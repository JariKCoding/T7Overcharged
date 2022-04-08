#include "file_watcher.hpp"
file_watcher::file_watcher()
{
    stopWatching();
    timeout = std::chrono::duration<int, std::milli>(10 * 1000);
    watcher_ = std::thread(&file_watcher::watcherFunction, this);
}

file_watcher& file_watcher::setTimeout(std::chrono::duration<int, std::milli> timer)
{
    timeout = timer;
    return *this;
}

file_watcher::~file_watcher()
{
    stopWatching();
}

file_watcher& file_watcher::startWatching()
{
    watching_ = true;
    return *this;
}

file_watcher& file_watcher::stopWatching()
{
    watching_ = false;
    return *this;
}

file_watcher& file_watcher::addFileToWatch(const std::string file)
{
    const std::filesystem::path file_path = file;
    std::optional<std::filesystem::file_time_type> value = std::nullopt;

    const std::lock_guard<std::mutex> lock(paths_mutex_);
    if (paths_.contains(file_path) || std::filesystem::is_directory(file_path))
        return *this;

    if (std::filesystem::exists(file_path))
        value = std::optional<std::filesystem::file_time_type>(std::filesystem::last_write_time(file_path));

    paths_[file_path] = value;
    return *this;
}

file_watcher& file_watcher::addFolderToWatch(const std::string folder)
{
    const std::filesystem::path folder_path = folder;
    const std::lock_guard<std::mutex> lock(paths_mutex_);

    if (paths_.contains(folder_path))
        return *this;

    std::optional<std::filesystem::file_time_type> value = std::nullopt;

    if (std::filesystem::exists(folder_path)) {
        value = std::optional<std::filesystem::file_time_type>(std::filesystem::last_write_time(folder_path));

        for (auto const path : std::filesystem::recursive_directory_iterator(folder_path))
        {
            paths_[path.path()] = std::filesystem::last_write_time(path);
        }
    }

    paths_[folder_path] = value;
    folders_.insert(folder_path);

    return *this;
}

file_watcher& file_watcher::addFileAction(const std::function<void(std::string, File_status)>& action)
{
    const std::lock_guard<std::mutex> lock(file_actions_mutex_);

    file_actions_.push_back(action);
    return *this;
}

file_watcher& file_watcher::addFolderAction(const std::function<void(std::string, Folder_status)>& action)
{
    const std::lock_guard<std::mutex> lock(folder_actions_mutex_);

    folder_actions_.push_back(action);
    return *this;
}


void file_watcher::watcherFunction()
{
    while (true)
    {
        std::this_thread::sleep_for(timeout);
        if (!watching_)
        {
            continue;
        }
        const std::lock_guard<std::mutex> lock_files(paths_mutex_);
        for (auto const path : paths_)
        {
            if (!std::filesystem::exists(path.first))
            {
                if (path.second.has_value())
                {
                    //File has been deleted
                    if (folders_.contains(path.first))
                    {
                        folder_changes_[path.first] = Folder_status::erased;
                    }
                    else
                    {
                        file_changes_[path.first] = File_status::erased;

                    }
                    paths_[path.first] = std::nullopt;
                }
            }
            else
            {
                std::optional<std::filesystem::file_time_type> newValue(std::filesystem::last_write_time(path.first));
                bool is_directory = (folders_.contains(path.first));
                if (!path.second.has_value())
                {
                    if (is_directory)
                    {
                        folder_changes_[path.first] = Folder_status::created;
                    }
                    else
                    {
                        file_changes_[path.first] = File_status::created;
                    }

                    paths_[path.first] = newValue;
                }
                else if (paths_[path.first] != newValue)
                {
                    if (is_directory)
                    {
                        folder_changes_[path.first] = Folder_status::modified;
                    }
                    else
                    {
                        file_changes_[path.first] = File_status::modified;
                    }
                    paths_[path.first] = newValue;
                }
                if (is_directory)
                {
                    for (auto const dirpath : std::filesystem::recursive_directory_iterator(path.first))
                    {
                        if (!paths_.contains(dirpath.path()))
                        {
                            paths_[dirpath.path()] = std::filesystem::last_write_time(dirpath);
                            if (std::filesystem::is_directory(dirpath.path()))
                            {
                                folders_.insert(dirpath.path());
                                folder_changes_[dirpath.path()] = Folder_status::created;
                            }
                            else
                            {
                                file_changes_[dirpath.path()] = File_status::created;
                            }
                        }
                    }
                }
            }
        }

        const std::lock_guard<std::mutex> lock_file_actions(file_actions_mutex_);
        fireFileActions();

        const std::lock_guard<std::mutex> lock_folder_actions(folder_actions_mutex_);
        fireFolderActions();
    }
}


void file_watcher::fireFileActions()
{
    for (const auto action : file_actions_)
    {
        for (const auto change : file_changes_)
        {
            action(change.first.string(), change.second);
        }
    }
    file_changes_.clear();
}

void file_watcher::fireFolderActions()
{
    for (const auto action : folder_actions_)
    {
        for (const auto change : folder_changes_)
        {
            action(change.first.string(), change.second);
        }
    }
    folder_changes_.clear();
}
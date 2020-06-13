#include <DirMan.h>
#include <experimental/filesystem>
#include <r_util.h>

using namespace rg;
namespace fs = std::experimental::filesystem;

/**
 * @brief Converts alias path to actual path.
 * 
 * @param path 
 * @return std::string 
 */
std::string DirMan::getActualPath(const std::string &path)
{
	
	std::size_t div = path.find(":");
	
	//Wrong format
	if (div == std::string::npos)
	{
		R_CPRINT_ERR("Invalid path format");
		return "";
	}

	auto it = _registered_paths.find(path.substr(0, div));

	//Could not find alias in _registered_paths
	if (it == _registered_paths.end())
	{
		R_CPRINT_ERR(("Path alias " + path.substr(0, div) + " not found.").c_str());
		return "";
	}

	std::string sub_path = path.substr(div + 1);

	return it->second + sub_path;
}


/**
 * @brief Check if file exists or not. "path" is alias path.
 * 
 * @param path 
 * @return true if exits.
 * @return false
 */
bool DirMan::fileExists(const std::string &path)
{
	return fs::is_regular_file(fs::path(getActualPath(path)));
}


/**
 * @brief Check if dir exists or not. "path" is alias path.
 * 
 * @param path 
 * @return true if exits.
 * @return false
 */
bool DirMan::dirExists(const std::string &path)
{
	return fs::is_directory(fs::path(getActualPath(path)));
}


/**
 * @brief Register path alias.
 * 
 * @param name alias.
 * @param path path to.
 */
void DirMan::registerPath(const std::string &name, const std::string &path)
{
	//Key exist
	if (_registered_paths.find(name) == _registered_paths.end())
	{
		R_CPRINT_ERR(("Key " + name + "already exist").c_str());
		return;
	}

	_registered_paths[name] = path;
}
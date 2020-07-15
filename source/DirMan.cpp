#include <RG/DirMan.h>
#include <experimental/filesystem>
#include <RG/r_util.h>

using namespace rg;
namespace fs = std::experimental::filesystem;

/**
 * @brief Converts alias path to actual path.
 * 
 * @param path 
 * @return std::string 
 */
std::string DirMan::getAliasPath(const std::string &alias)
{
	auto pair = _alias_paths.find(alias);
	
	if (pair != _alias_paths.end())
		return "";
	else
		return pair->second;
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
	auto strings = rg::util::splitStr(path,">");
	if (strings.size() > 1)
		return fs::is_regular_file(getAliasPath(strings[0]) + "/" + strings[1] );
	
	return fs::is_regular_file( getAliasPath(path) );
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
	auto strings = rg::util::splitStr(path,">");
	if (strings.size() > 1)
		return fs::is_directory( getAliasPath(strings[0]) + "/" + strings[1] );
	
	return fs::is_directory( getAliasPath(path) );
}


/**
 * @brief Register path alias.
 * 
 * @param name alias.
 * @param path path to.
 */
void DirMan::registerAlias(const std::string &alias, const std::string &path)
{	
	auto pair = _alias_paths.find(alias);

	// Key exist, update value
	if (pair != _alias_paths.end())
		pair->second = path;
	else
		_alias_paths[alias] = path;
}
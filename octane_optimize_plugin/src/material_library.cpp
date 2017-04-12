#include "material_library.h"

#include "utils.h"
#include "octane_lua_api.h"
#include "sol.hpp"

material::MaterialLibrary::MaterialLibrary(const std::string& libraryPath)
{
	library_path_ = libraryPath;
}

material::MaterialLibrary::~MaterialLibrary()
{
	
}

void material::MaterialLibrary::Load() const
{
	//�õ����е�ocs�ļ�,ÿһ��ocs�ļ��ж�������һ��ģ��
	//��������Щ����ģ����뵽��������ȥ
	octane_lua_api::OCtaneLuaAPI& octane_lua_api_instance = octane_lua_api::OCtaneLuaAPI::Get();

	if (!octane_plug_utils::IsDirExist(library_path_))
	{
		return;
	}

	std::vector<std::string> model_ocs_files{};
	sol::object root_scene = octane_lua_api_instance["octane"]["project"]["getSceneGraph"]();
	sol::object temp_scene = octane_lua_api_instance["octane"]["nodegraph"]["createRootGraph"]("temp_graph");
	int file_num = octane_plug_utils::GetAllFilesPath(library_path_, model_ocs_files);
	for (const auto& file_path: model_ocs_files)
	{
		if (octane_plug_utils::get_file_ext_with_dot(file_path) == ".ocs")
		{
			octane_lua_api_instance["octane"]["nodegraph"]["importFromFile"](temp_scene, file_path);
			octane_lua_api_instance["octane"]["nodegraph"]["copyFromGraph"](root_scene, temp_scene);
		}
	}
}

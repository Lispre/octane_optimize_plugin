// ��־����
#define ELPP_NO_DEFAULT_LOG_FILE
#define ELPP_THREAD_SAFE
#define SOL_CHECK_ARGUMENTS

#include <stdio.h>

#include "sol.hpp"
#include "utils.h"
#include "octane_lua_api.h"
#include "xml_rw.h"
//#include "scene_data.h"
#include "config_file.h"
#include "download_uploader.h"

#include "easylogging++.h"
#include "main_window.h"
#include "modify_window.h"
#include "test_image_window.h"

INITIALIZE_EASYLOGGINGPP

constexpr char* config_file_name = "octane_plugin.cfg";

void Easylogging_Setup()
{
    //����easylogging�����ļ�
    el::Configurations conf("easylogging++_conf.txt");
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
    el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
}

static sol::state_view* octane_lua_container{ nullptr };

int test_function()
{
    LOG(INFO) << "fuck the refactor of octane plugin!" << std::endl;
    return 0;
}

extern "C" __declspec(dllexport) int luaopen_octane_optimize_plugin(lua_State* L)
{
    using octane_plug_utils::CheckType;
    using octane_plug_utils::TraverseTable;
    using octane_plug_utils::pair_print;

    // �������ڱ�����־��Ŀ¼
    octane_plug_utils::CreateFolder("log");

	// �������ڱ�������ģ���ļ���Ŀ¼
	std::string octane_download_folder = octane_plug_utils::find_first_available_driver() + "octane_plugin_download_folder";
	if (!octane_plug_utils::IsDirExist(octane_download_folder))
	{
	    octane_plug_utils::CreateFolder(octane_download_folder);
	}

    // ��ʼ����־
    Easylogging_Setup();

    // ���octane_lua_container���Ƕ�octane lua����������
    octane_lua_container = new sol::state_view(L);
    octane_lua_api::OCtaneLuaAPI& octane_lua_api_instance = octane_lua_api::OCtaneLuaAPI::Get();
    octane_lua_api_instance.Setup(octane_lua_container);

    config_file::ConfigFile& config_file_instance = config_file::ConfigFile::Get();
    config_file_instance.Setup(octane_download_folder + "\\" + config_file_name);
    auto download_uploader_instance = new download_upload::DownloadUploader();

    gui::MainWindow* main_window = new gui::MainWindow();
    main_window->ShowWindow();

    return 0;
}
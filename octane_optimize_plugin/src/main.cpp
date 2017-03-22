// ��־����
#define ELPP_NO_DEFAULT_LOG_FILE
#define ELPP_THREAD_SAFE
#define SOL_CHECK_ARGUMENTS

#include <stdio.h>

#include "sol.hpp"
#include "utils.h"
#include "octane_lua_api.h"
#include "xml_rw.h"
#include "scene_data.h"
#include "config_file.h"
#include "download_uploader.h"

#include "easylogging++.h"
#include "main_window.h"

INITIALIZE_EASYLOGGINGPP

constexpr char* config_file_name = "config_test.cfg";

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

    // ��ʼ����־
    Easylogging_Setup();

    // ���octane_lua_container���Ƕ�octane lua����������
    octane_lua_container = new sol::state_view(L);
    octane_lua_api::OCtaneLuaAPI& octane_lua_api_instance = octane_lua_api::OCtaneLuaAPI::Get();
    octane_lua_api_instance.Setup(octane_lua_container);

    xml_rw::XMLHandler& xml_handler_instance = xml_rw::XMLHandler::Get();
    xml_handler_instance.Init();
    //��ȡ�����������, �����ɺͲ��뵽xml��
    scene_data::get_scene_node_data();

    //�Ը�����������Ĵ���, ��Ϊ�����Ҫ�����ض�����Ϣ
    scene_data::get_root_node_data();

    // �������յ���Ϣ���ļ���
    xml_rw::XMLHandler::Get().SaveFile("fuck_test_save_file.ocs");
    config_file::ConfigFile& config_file_instance = config_file::ConfigFile::Get();
    config_file_instance.Setup(config_file_name);
    auto download_uploader_instance = new download_upload::DownloadUploader();

    

#if 0
    if (download_uploader_instance->DownloadFileFromOCS("846675380d4911e7b9fa00163e1284d1") == common_types::LoadResult::download_failed)
    {
    //�������ش���
    //download_uploader_instance->error_message_
        return 0;
    }

    auto extract_dir = octane_plug_utils::extract_zip_file(download_uploader_instance->LastStoredFileFullPathName);
    if (extract_dir.empty())
    {
    //��ѹʧ��
    }
    if (octane_plug_utils::IsDirExist(extract_dir + "\\octane"))
    {
        config_file_instance.Write("LastExtractFolderPath", extract_dir);
        octane_lua_api_instance["octane"]["project"]["load"](extract_dir + "\\octane\\item.ocs");
    }
    else if (octane_plug_utils::IsDirExist(extract_dir + "\\item.ocs"))
    {
        config_file_instance.Write("LastExtractFolderPath", extract_dir);
        octane_lua_api_instance["octane"]["project"]["load"](extract_dir + "\\item.ocs");
    }
    else
    {
    // ��������, ����Ŀ¼��ʽ����
    }
#endif
#if 0
    std::string extract_dir1 = std::get<0>(config_file_instance.Read("LastExtractFolderPath"));
    //�����������ĸ���������Ƶ�ʧ��,����˵�ʧ��
    octane_plug_utils::CreateAndMove(extract_dir1, "octane");
    std::string zip_file_path = octane_plug_utils::compress_folder(extract_dir1, "item.zip");
    if (zip_file_path.empty())
    {
    //�������
    }
    download_uploader_instance->UploadFileToOCS("846675380d4911e7b9fa00163e1284d1", "846675380d4911e7b9fa00163e1284d1/octane.zip", zip_file_path);
#endif
    gui::MainWindow* main_window = new gui::MainWindow();
    main_window->ShowWindow();

    return 0;
}
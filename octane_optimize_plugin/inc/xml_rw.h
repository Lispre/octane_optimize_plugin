#pragma once

#include <map>

#include "pugixml.hpp"
#include "pugiconfig.hpp"

namespace xml_rw {
	
	class XMLHandler {
	public:
		XMLHandler(const XMLHandler&) = delete;
		XMLHandler& operator =(const XMLHandler&) = delete;
		XMLHandler(const XMLHandler&&) = delete;
		XMLHandler& operator =(const XMLHandler&&) = delete;

		static XMLHandler& Get();
		~XMLHandler();
		
		bool SaveFile(const std::string& file_name) const;

		// ��ʼ��xml�ļ�, ����������
		void Init();
		
		// ��������
		std::string InsertRootNode(const std::string& father_node_path,
			const std::string& node_name,
			const std::pair<std::string, std::string>* diff_pair,
			const std::map<std::string, std::string>& attributes) const;

		// ����PIN���
		std::string InsertPin(const std::string& father_node_path,
			const std::pair<std::string, std::string>* diff_pair,
			const std::map<std::string, std::string>& attributes) const;

		// �������Խ��
		std::string InsertAttributeNode(const std::string& father_node_path,
			const std::pair<std::string, std::string>* diff_pair,
			const std::map<std::string, std::string>& attributes,
			const std::string& pcdata) const;

		/**
		 * ������XML���в���һ���µĽ��
		 * @father_node_path: ��ʾ������ڵ��²����µĽڵ�
		 * @node_name: �½�������
		 * @attri_key_value: һ����ֵ�����ڴ�������ͬ�Ľڵ��Ψһȷ���������
		 * @attribute: ����������Լ�
		 * �ɹ����ز�����½���·��, ʧ�ܷ��ظ�����·��
		 */
		std::string InsertNode(const std::string& father_node_path, 
			const std::string& node_name, 
			const std::pair<std::string, std::string>* attr_key_value,
			const std::map<std::string, std::string>& attributes,
			const std::string& pcdata) const;
	private:

		XMLHandler();
		pugi::xml_document* doc = nullptr;
	};

}

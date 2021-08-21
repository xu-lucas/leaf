#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<unordered_map>
#include "httplib.h"
#ifdef _WIN32
#include<filesystem>
#include<windows.h>
#else
#include<experimental/filesystem>
#include<unistd.h>
#endif

namespace cloud_sys {
	namespace fs = std::experimental::filesystem;
	class ScanDir {
	public:
		ScanDir(const std::string& path) :_path(path)
		{
			if (!std::experimental::filesystem::exists(path))
			{
				std::experimental::filesystem::create_directories(path);
			}
			if (_path.back() != '/')
			{
				_path += '/';
			}
		}
		bool Scan(std::vector<std::string>* arry)
		{
			for (auto& file : std::experimental::filesystem::directory_iterator(_path))
			{
				std::string name;
				name = file.path().filename().string();
				arry->push_back(_path + name);
			}
			return true;
		}
	private:
		std::string _path;
	};
	class Util {
	public:
		static bool FileRead(const std::string& file, std::string* body)
		{
			std::ifstream in;
			in.open(file, std::ios::binary);
			if (in.is_open() == false)
			{
				std::cout << "open file failed\n";
				return false;
			}
			uint64_t size = std::experimental::filesystem::file_size(file);
			body->resize(size);
			in.read(&(*body)[0], size);
			if (in.good() == false)
			{
				std::cout << "read file failed!\n";
				return false;
			}
			in.close();
			return true;
		}
		static bool FileWrite(const std::string& file, const std::string& body)
		{
			std::ofstream out;
			out.open(file, std::ios::binary);
			if (out.is_open() == false)
			{
				std::cout << "open file failed\n";
				return false;
			}
			out.write(&body[0], body.size());
			if (out.good() == false)
			{
				std::cout << "write file failed!\n";
				return false;
			}
			out.close();
			return true;
		}
		static int Split(const std::string& str, const std::string& sp,
			std::vector<std::string>* arry)
		{
			int count = 0;
			size_t pos, idx = 0;
			while (1)
			{
				pos = str.find(sp, idx);
				if (pos == std::string::npos)
					break;
				arry->push_back(str.substr(idx, pos - idx));
				idx = pos + sp.size();
				count++;
			}
			if (idx < str.size())
			{
				count++;
				arry->push_back(str.substr(idx));
			}
			return count;
		}
	};
	class DataManager {
	public:
		DataManager(const std::string& path) :_path(path) {}

		bool Read()
		{
			std::string body;
			std::vector<std::string> arry;
			if (Util::FileRead(_path, &body) == false)
			{
				std::cout << "read data set failed!\n";
				return false;
			}
			Util::Split(body, "\n", &arry);
			for (auto& line : arry)
			{
				std::vector<std::string> kv;
				Util::Split(line, "=", &kv);
				_map[kv[0]] = kv[1];
			}
			return true;
		}

		bool Write()
		{
			//key=val\n...
			std::stringstream ss;
			for (auto it : _map)
			{
				ss << it.first << "=" << it.second << "\n";
			}
			if (Util::FileWrite(_path, ss.str()) == false)
			{
				std::cout << "write data set failed!\n";
				return false;
			}
			return true;
		}

		bool Exists(const std::string& key)
		{
			auto it = _map.find(key);
			if (it == _map.end())
			{
				return false;
			}
			return true;
		}
		bool AddOrMod(const std::string& key, const std::string& val)
		{
			if (Exists(key) == true)
			{
				std::cout << key << "   exists!\n";
				return false;
			}
			_map[key] = val;
			return true;
		}

		bool Del(const std::string& key, const std::string& val)
		{
			auto it = _map.find(key);
			if (it == _map.end())
			{
				std::cout << key << "  not exists!\n";
				return false;
			}
			_map.erase(it);
			return true;
		}

		bool Get(const std::string& key, std::string* val)
		{
			auto it = _map.find(key);
			if (it == _map.end())
			{
				std::cout << key << "  not exists!\n";
				return false;
			}
			*val = _map[key];
			return true;
		}
	private:
		std::string _path;
		std::unordered_map<std::string, std::string> _map;
	};

#define LISTEN_DIR "./scandir"
#define CONFIG_FILE "./data.conf"

	class Client {
	public:
		Client(const std::string& host, int port) :_scan(LISTEN_DIR), _data(CONFIG_FILE)
		{
			_client = new httplib::Client(host, port);
		}
		std::string GetIdentifier(const std::string& path)
		{
			uint64_t mtime, fsize;
			fsize = std::experimental::filesystem::file_size(path);
			auto time_type = std::experimental::filesystem::last_write_time(path);

			mtime = decltype(time_type)::clock::to_time_t(time_type);
			std::stringstream ss;
			ss << fsize << mtime;
			return ss.str();
		}
		
		bool Scan(std::vector<std::pair<std::string, std::string>>* arry)
		{
			
			std::vector<std::string> files;
			_scan.Scan(&files);
			
			for (auto& file : files)
			{
				std::string identifier = GetIdentifier(file);
				if (_data.Exists(file) == false)
				{
					arry->push_back(std::make_pair(file, identifier));
					continue;
				}
				std::string old;
				_data.Get(file, &old);
				if (old == identifier) 
				{
					continue;
				}
				arry->push_back(std::make_pair(file, identifier));
			}
			return true;
		}
		bool Upload(const std::string& path)
		{
			httplib::MultipartFormData file;
			file.name = "file";
			file.content_type = "application/octet-stream";
			fs::path p(path);
			file.filename=p.filename().string();
			Util::FileRead(path, &file.content);

			httplib::MultipartFormDataItems items;
			items.push_back(file);
			
			auto rsp=_client->Post("/multipart",items);
			if (rsp && rsp->status ==200) 
			{
				std::cout << "upload succeed!\n";
				return true;
			}
			std::cout << "upload filed!\n";
			return false;
		}

		bool Start() 
		{
			_data.Read();
			while (1) {
				std::vector<std::pair<std::string, std::string>> arry;
				Scan(&arry);
				for (auto &file : arry)
				{
					std::cout << file.first << "   Need Upload\n";
					if (Upload(file.first)== false)
					{
					  continue;
					}
					_data.AddOrMod(file.first, file.second);
					_data.Write();
				}
				Sleep(1000);
			}
			return true;
		}
	private:
		ScanDir _scan;
		DataManager _data;
		httplib::Client* _client;
	};
}
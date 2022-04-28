#pragma once
#include <string>

namespace Eyes2D {
	namespace Platform {
		//���ļ�·����ʽת��ΪWindows��ʽ
		inline void PathFormatWin32(char* str, int strlen) {
			for (int index = 0; index < strlen; index++) {
				char& ref = str[index];
				if (ref == '/') {
					ref = '\\';
				}
			}
		}

		inline void PathFormatWin32(wchar_t* str, int strlen) {
			for (int index = 0; index < strlen; index++) {
				wchar_t& ref = str[index];
				if (ref == L'/') {
					ref = L'\\';
				}
			}
		}

		inline void PathFormatWin32(std::string& str) {
			for (auto& c : str) {
				if (c == '/') {
					c = '\\';
				}
			}
		}

		inline void PathFormatWin32(std::wstring& str) {
			for (auto& c : str) {
				if (c == L'/') {
					c = L'\\';
				}
			}
		}

		//���ļ�·����ʽת��ΪWindows��ʽ��������Сд��Windowsϵͳ�ж�
		inline void PathFormatWin32LowCase(char* str, int strlen) {
			for (int index = 0; index < strlen; index++) {
				char& ref = str[index];
				if (ref == '/') {
					ref = '\\';
				}
				else if ((ref >= 'A') && (ref <= 'Z')) {
					ref = ref - 'A' + 'a';
				}
			}
		}

		inline void PathFormatWin32LowCase(wchar_t* str, int strlen) {
			for (int index = 0; index < strlen; index++) {
				wchar_t& ref = str[index];
				if (ref == L'/') {
					ref = L'\\';
				}
				else if ((ref >= L'A') && (ref <= L'Z')) {
					ref = ref - L'A' + L'a';
				}
			}
		}

		inline void PathFormatWin32LowCase(std::string& str) {
			for (auto& c : str) {
				if (c == '/') {
					c = '\\';
				}
				else if ((c >= 'A') && (c <= 'Z')) {
					c = c - 'A' + 'a';
				}
			}
		}

		inline void PathFormatWin32LowCase(std::wstring& str) {
			for (auto& c : str) {
				if (c == L'/') {
					c = L'\\';
				}
				else if ((c >= L'A') && (c <= L'Z')) {
					c = c - L'A' + L'a';
				}
			}
		}

		//���ļ�·����ʽת��ΪLinux��ʽ��Linuxϵͳ���ļ�ϵͳ��·����Сд����
		inline void PathFormatLinux(char* str, int strlen) {
			for (int index = 0; index < strlen; index++) {
				char& ref = str[index];
				if (ref == '\\') {
					ref = '/';
				}
			}
		}

		inline void PathFormatLinux(wchar_t* str, int strlen) {
			for (int index = 0; index < strlen; index++) {
				wchar_t& ref = str[index];
				if (ref == L'\\') {
					ref = L'/';
				}
			}
		}

		inline void PathFormatLinux(std::string& str) {
			for (auto& c : str) {
				if (c == '\\') {
					c = '/';
				}
			}
		}

		inline void PathFormatLinux(std::wstring& str) {
			for (auto& c : str) {
				if (c == L'\\') {
					c = L'/';
				}
			}
		}
	}
}

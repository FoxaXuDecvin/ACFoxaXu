//zip_un.h
#pragma once
#include <Windows.h>          //添加Windows.h不然会一堆错误
#include <string>             //C++使用string添加string,不要添加string.h
#include <iostream>
#include <tchar.h>
#include <vector>
#include <io.h>
#include "zip.h"
#include "unzip.h"
using namespace std;

class zip_un {
public:
	int Zip_UnPackFiles(string strZipPath);
	void Zip_PackFiles(string path);
	zip_un();

private:
	HZIP hz;
	void browseFile(string inPath);
	WCHAR* toWchar(string strZipPath);
	vector<string> split(const string& str);
	string connectStr(vector<string>& ret);
	string temporaryPath;
	int index; //用于深度搜索的标识
};

// 原文链接：https://blog.csdn.net/weixin_43892561/article/details/110149754
\
zip_un::zip_un() {
	index = 0;
}
vector<string> zip_un::split(const string& str){
	vector<string> ret;
	const string pattern = "\\";
	/*if (pattern.empty())
		return ret;*/
	int stat = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos) {
		if (stat != index)
			ret.push_back(str.substr(stat, index - stat));
		stat = index + 1;
		index = str.find_first_of(pattern, stat);
	}
	if (!str.substr(stat).empty())
		ret.push_back(str.substr(stat));
	return ret;
}
string zip_un::connectStr(vector<string>& ret) {
	string c;
	ret[ret.size() - 1] = ret[ret.size() - 1].substr(0, ret[ret.size() - 1].size() - 4);
	for (int i = 0;i < ret.size();i++) {
		c += ret[i] + "\\";
	}
	return c;
}
int zip_un::Zip_UnPackFiles(string strZipPath){
	string strZipPath_un = strZipPath;
	vector<string> mUn = split(strZipPath);
	const WCHAR* pwUnicode = toWchar(strZipPath_un);
	string a = "mkdir -p " + connectStr(mUn);
	system(a.c_str());  //创建文件
	//解压文件
	//SetCurrentDirectory(_T("D:\\c++_project"));//将进程的工作目录移动到该参数所指的目录下,该目录为winrar.exe的默认文件路径
	SetCurrentDirectoryA(connectStr(mUn).c_str());
	//解压文件会直接在项目的.vcproj目录下进行
	HZIP hz = OpenZip(pwUnicode, NULL);
	
	ZIPENTRY ze;
	GetZipItem(hz, -1, &ze);  // -1给出关于zip文件整体信息
	int numitems = ze.index;
	for (int zi = 0; zi < numitems; zi++)
	{
		ZIPENTRY ze;
		GetZipItem(hz, zi, &ze);
		UnzipItem(hz, zi, ze.name);
		cout << "解压成功" << endl;
	}
	CloseZip(hz);
	return 0;
}

WCHAR* zip_un::toWchar(string strZipPath){
	string strZipPath_un = strZipPath;
	//将路径转为TCHAR类型
	int iUnicode = MultiByteToWideChar(CP_ACP, 0, strZipPath_un.c_str(), strZipPath_un.length(), NULL, 0);
	WCHAR* pwUnicode = new WCHAR[iUnicode + 2];
	if (pwUnicode)
	{
		ZeroMemory(pwUnicode, iUnicode + 2);
	}
	MultiByteToWideChar(CP_ACP, 0, strZipPath_un.c_str(), strZipPath_un.length(), pwUnicode, iUnicode);
	pwUnicode[iUnicode] = '\0';
	pwUnicode[iUnicode + 1] = '\0';
	return pwUnicode;
}

void zip_un::browseFile(string inPath) {
	string path = inPath + "\\*.*", filePath;
	struct _finddata_t fileinfo;
	long handle = _findfirst(path.c_str(), &fileinfo);
	if (handle == -1)
		exit(0);
	do{
		if (fileinfo.attrib & _A_SUBDIR){  //为目录
			//ZipAddFolder(hz, toWchar(fileinfo.name));		
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0) continue;
			index++;
			vector<string> aa = split(inPath);
			for (int i = index;i > 0;i--) {
				temporaryPath = temporaryPath + aa[aa.size() - i] + "\\";
			}
			ZipAddFolder(hz, toWchar(temporaryPath + fileinfo.name));
			temporaryPath.clear();
			string dirNew = inPath + "\\" + fileinfo.name;
			browseFile(dirNew);	
			index--;
		} 
		else {
			filePath = inPath + "\\" ;
			vector<string> aa = split(inPath);
			for (int i = index+1;i > 0;i--) {
				temporaryPath = temporaryPath + aa[aa.size() - i] + "\\";
			}
			ZipAdd(hz, toWchar(temporaryPath + fileinfo.name  ), toWchar(filePath  + fileinfo.name));
			temporaryPath.clear();
		}
	} while (!_findnext(handle, &fileinfo));
	_findclose(handle);
}

void zip_un::Zip_PackFiles(string path) {
	string  path_1 = path + ".zip";
	hz = CreateZip(toWchar(path_1), 0);
	browseFile(path);
	CloseZip(hz);
}

int MakeZip(string file){
    zip_un z;
	string strZipPath_un, strZipPath = "D:\\c++_project\\2";
	strZipPath_un = strZipPath + ".zip";
	z.Zip_PackFiles(strZipPath);
    return 1
}
#include "main_MainController.h"
#include <vector>
#include <string>
#include <Windows.h>

#ifndef UNICODE  
typedef std::string string;
#else
typedef std::wstring string;
#endif

/*
 * Class:     main_MainController
 * Method:    getComPorts
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_main_MainController_getComPorts(JNIEnv* env, jobject obj)
{
	std::vector<string> ports;
	size_t upperLimit = 32;
	for (size_t i = 1; i <= upperLimit; i++)
	{
		TCHAR strPort[32] = { 0 };

		DWORD dwSize = 0;
		LPCOMMCONFIG lpCC = (LPCOMMCONFIG) new BYTE[1];
		BOOL ret = GetDefaultCommConfig(strPort, lpCC, &dwSize);
		delete[] lpCC;

		lpCC = (LPCOMMCONFIG) new BYTE[dwSize];
		ret = GetDefaultCommConfig(strPort, lpCC, &dwSize);
		delete[] lpCC;

		if (ret) ports.push_back(strPort);
	}
	jobjectArray result = (jobjectArray)env->NewObjectArray(ports.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));
	for (int i = 0; i < ports.size(); i++)
	{
		env->SetObjectArrayElement(result, i, env->NewStringUTF((char *)ports[i].c_str()));
	}
	return result;

}
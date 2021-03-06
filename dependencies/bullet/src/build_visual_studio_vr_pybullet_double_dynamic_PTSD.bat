IF NOT EXIST bin mkdir bin
IF NOT EXIST bin\openvr_api.dll  copy examples\ThirdPartyLibs\openvr\bin\win32\openvr_api.dll bin
IF NOT EXIST bin\openvr64pi.dll  copy examples\ThirdPartyLibs\openvr\bin\win64\openvr_api.dll bin\openvr64pi.dll

rem #aargh, see https://github.com/ValveSoftware/openvr/issues/412


rem #find a python version (hopefully just 1) and use this
set inPy=%1
dir %inPy%\python* /b /ad > tmp1234.txt

set /p myvar1= < tmp1234.txt
set "inPy=%inPy:\=/%"
set myvar= %inPy%/%myvar1%
set myvar=%myvar:~1%
del tmp1234.txt

rem you can also override and hardcode the Python path like this (just remove the # hashmark in next line)
rem SET myvar=c:\python-3.5.2

cd build3

premake4  --dynamic-runtime --double --standalone-examples --enable_stable_pd --enable_multithreading --midi --enable_static_vr_plugin --enable_openvr --enable_pybullet --python_include_dir="%myvar%/include" --python_lib_dir="%myvar%/libs"   --targetdir="../bin" vs2010 

rem premake4  --double   --enable_multithreading --midi --enable_static_vr_plugin --enable_openvr --enable_pybullet --python_include_dir="%myvar%/include" --python_lib_dir="%myvar%/libs"   --targetdir="../binserver" vs2010 
rem premake4  --double --enable_grpc --enable_multithreading --midi --enable_static_vr_plugin --enable_openvr --enable_pybullet --python_include_dir="%myvar%/include" --python_lib_dir="%myvar%/libs"   --targetdir="../binserver" vs2010 
rem premake4  --serial --audio --double --midi --enable_openvr --enable_pybullet --python_include_dir="%myvar%/include" --python_lib_dir="%myvar%/libs"   --targetdir="../bin" vs2010 
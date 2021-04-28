:: Build Bullet

set arg1=%1
if exist src\build3\vs2010\ goto done
cd src
call build_visual_studio_vr_pybullet_double_dynamic_PTSD.bat %arg1%
cd vs2010

MSBuild 0_Bullet3Solution.sln /t:pybullet /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v142
MSBuild 0_Bullet3Solution.sln /t:pybullet /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v142

cd ..\..\..\
goto end

:done
echo Bullet already built
:end
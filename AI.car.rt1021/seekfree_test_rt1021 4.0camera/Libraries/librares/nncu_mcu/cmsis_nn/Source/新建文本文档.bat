@echo off

for /f "delims=" %%a in ('dir /b/a-d/oN *.*') do echo %%a >>当前文件夹内文件名.txt
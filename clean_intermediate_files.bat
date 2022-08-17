@echo off
set DirsToRemove=Intermediate Saved DerivedDataCache Binaries Binaries Build .vs
set FilesToRemove=*.sln

for %%a in (%DirsToRemove%) do (
    rmdir /S /Q %%a
)

for %%a in (%FilesToRemove%) do (
   del %%a
)

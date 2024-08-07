
## oracle oci develop

https://www.oracle.com/database/technologies/instant-client/winx64-64-downloads.html



### 1. Download Basic Package

Configure environment variables:
Path: .../ocis/instantclient_23_4/



### 2. Download SDK Package
```


## include:
include_directories(
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/ocis/instantclient_23_4/sdk/include/
)

## link:
file(GLOB StaticLibs ${CMAKE_SOURCE_DIR}/ocis/instantclient_23_4/sdk/lib/msvc/*.lib)
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${StaticLibs}
)

```


### 3. build
```
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Debug ..
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release ..
```

### 4. commit

```
git lfs install
git lfs track "*.dll"
git add *.dll
git commit -m "Track large files with Git LFS"
git push
```

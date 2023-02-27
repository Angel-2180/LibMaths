# LibMaths

## Installation

Using CMake, FetchContent the git repository

```cmake
# Include FetchContent
include("FetchContent")

# Fetch for hlm
FetchContent_Declare(
    libMath
    GIT_REPOSITORY https://github.com/Angel-2180/LibMaths.git
    )

# Before creating your executable
FetchContent_MakeAvailable(libMath)

# To include the library
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBMATHS_INCLUDE_DIR})

# To link the library
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBMATHS_LIBRARY})
```



## Usage

```cpp
#include <Mat4/FMat4.hpp> // Import the 4x4 Matrix
#include <Vec3/FVec3.hpp>

// Create a projection, view and model matrix
lm::FMat4 g_ProjectionMatrix = lm::FMat4::Perspective(90.f, 1920/1080, 0.1f,1000.f);
lm::FMat4 g_ViewMatrix = lm::FMat4::LookAt(lm::FVec3(0,0,0),lm::FVec3(1,1,1),lm::FVec3(0,1,0));
lm::FMat4 g_ModelMatrix = lm::FMat4::Identity();

// Calculate the MVP
lm::FMat4 CalculateMVP(lm::FMat4& pModelMatrix, lm::FMat4& pViewMatrix,lm::FMat4& pProjectionMatrix)
{
    return pModelMatrix * pViewMatrix * pProjectionMatrix;
}

```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.
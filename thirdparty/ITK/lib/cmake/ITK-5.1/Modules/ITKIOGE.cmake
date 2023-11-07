set(ITKIOGE_LOADED 1)
set(ITKIOGE_ENABLE_SHARED "1")
set(ITKIOGE_DEPENDS "ITKIOIPL;ITKIOImageBase")
set(ITKIOGE_PUBLIC_DEPENDS "ITKIOIPL")
set(ITKIOGE_TRANSITIVE_DEPENDS "ITKIOIPL")
set(ITKIOGE_PRIVATE_DEPENDS "ITKIOImageBase")
set(ITKIOGE_LIBRARIES "ITKIOGE")
set(ITKIOGE_INCLUDE_DIRS "${ITK_INSTALL_PREFIX}/include/ITK-5.1")
set(ITKIOGE_LIBRARY_DIRS "")
set(ITKIOGE_RUNTIME_LIBRARY_DIRS "${ITK_INSTALL_PREFIX}/bin")
set(ITKIOGE_TARGETS_FILE "")
set(ITKIOGE_FACTORY_NAMES "ImageIO::GE4;ImageIO::GE5")


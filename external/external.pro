! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

shaders.path = $$(BUILD_DIR)
shaders.files = per-fragment-phong*

INSTALLS += shaders

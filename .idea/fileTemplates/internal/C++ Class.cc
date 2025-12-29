#if($DIR_PATH.contains("Editor"))
#parse ("Editor Source File Header.h")
#end
#if($DIR_PATH.contains("Engine"))
#parse ("Engine Source File Header.h")
#end



namespace ${NAMESPACES_OPEN}
{

} //${NAMESPACES_CLOSE}
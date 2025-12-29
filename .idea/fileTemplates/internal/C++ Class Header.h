#[[#pragma]]# once
#if($DIR_PATH.contains("Editor"))
#parse("Editor Header File Header.h")
#end
#if($DIR_PATH.contains("Engine"))
#parse("Engine Header File Header.h")
#end

namespace ${NAMESPACES_OPEN}
{

    class ${NAME} 
    {
    public:
     ${NAME}();
     ~${NAME}();
    private:
    }; 

} //${NAMESPACES_CLOSE}
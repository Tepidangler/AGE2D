#set( $ORGANIZATION_NAME = "Alcoy Game Studios")
#set( $NAMESPACES_OPEN = "AGE")
#set( $NAMESPACES_CLOSE = "AGE")
#set( $AUTHOR_NAME = "De'Lano Wilcox")
#if ($HEADER_COMMENTS)
//
// Created by $AUTHOR_NAME on ${DATE}.
#if ($ORGANIZATION_NAME && $ORGANIZATION_NAME != "")
// Copyright (c) $YEAR ${ORGANIZATION_NAME}#if (!$ORGANIZATION_NAME.endsWith(".")).#end All rights reserved.
#end
//
#end
#[[#include]]# "Core/Public/AGEpch.hpp"
#[[#include]]# "../Public/${NAME}.h"
#pragma once

#include <any>

#include <rapidjson.h>
#include <istreamwrapper.h>
#include <filereadstream.h>
#include <reader.h>
#include <prettywriter.h>
#include <writer.h>
#include <stringbuffer.h>
#include <document.h>
#include <stdexcept>               // std::runtime_error
#include <error/error.h>
#include <error/en.h>
#include <stringbuffer.h>

#include <type.h>
#include <property.h>
#include <variant_impl.h>
#include <variant.h>
#include <registration.h>
#include <version.h>

#include <fstream>
#include <filesystem>

#include "RTTR.h"
#include "JSONSerializer.h"
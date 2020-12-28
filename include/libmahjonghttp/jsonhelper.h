#pragma once

#include "event.h"
#include "piecetype.h"

#include <string>
#include <vector>
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"

using rapidjson::StringBuffer;
using rapidjson::Writer;
using rapidjson::Document;
using rapidjson::Value;

using Mahjong::Event;
using Mahjong::Piece;

namespace MahjongHttp {
  namespace JSONHelper {
    auto canParseEvent(Document&) -> bool;
    auto parseEvent(Document&) -> Event;
    auto parseEvent(Value&) -> Event;

    // Overload Function Mapping for Writing JSON values
    auto writeValue(Writer<StringBuffer>&, std::string) -> void;
    auto writeValue(Writer<StringBuffer>&, const char *) -> void;
    auto writeValue(Writer<StringBuffer>&, unsigned int) -> void;
    auto writeValue(Writer<StringBuffer>&, int) -> void;
    auto writeValue(Writer<StringBuffer>&, bool) -> void;
    auto writeValue(Writer<StringBuffer>&, Event) -> void;
    auto writeValue(Writer<StringBuffer>&, Piece) -> void;

    template <typename T>
    auto writeValue(Writer<StringBuffer>& writer, std::vector<T> list) -> void {
        writer.StartArray();
        for (const auto& value : list) {
          writeValue(writer, value);
        }
        writer.EndArray();
    }

    // Pair writing using above functions
    template <typename V>
    auto writePair(Writer<StringBuffer>& writer, std::string key, V value) -> void {
      writeValue(writer, key);
      writeValue(writer, value);
    }
  }
}

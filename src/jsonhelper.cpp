#include "jsonhelper.h"

#include <string>

#include "rapidjson/stringbuffer.h"

#include "event.h"

using rapidjson::StringBuffer;
using rapidjson::SizeType;
using rapidjson::Document;
using rapidjson::Value;

using Mahjong::Event;
using namespace MahjongHttp;

auto JSONHelper::canParseEvent(Document& d) -> bool {
  // Check Membership
  if (!d.HasMember("type") || !d.HasMember("player") || !d.HasMember("piece") || !d.HasMember("decision")) {
    return false;
  }

  auto& type = d["type"];
  auto& player = d["player"];
  auto& piece = d["piece"];
  auto& decision = d["decision"];

  // Check Type
  if (!type.IsUint() || !player.IsInt() || !piece.IsInt() || !decision.IsBool()) {
    return false;
  }

  // Check Type Range
  auto typeValue = type.GetUint();
  if (typeValue < Event::Type::Ron || typeValue > Event::Type::End) {
    return false;
  }

  return true;
}

auto JSONHelper::parseEvent(Document& d) -> Event {
  return Event {
    (Event::Type) d["type"].GetUint(),
    d["player"].GetInt(),
    (int16_t) d["piece"].GetInt(),
    d["decision"].GetBool(),
  };
}

auto JSONHelper::writeValue(Writer<StringBuffer>& writer, std::string str) -> void {
  writer.String(str.c_str(), static_cast<SizeType>(str.length()));
}

auto JSONHelper::writeValue(Writer<StringBuffer>& writer, const char* chrStr) -> void {
  writer.String(chrStr, static_cast<SizeType>(std::strlen(chrStr)));
}

auto JSONHelper::writeValue(Writer<StringBuffer>& writer, unsigned int unum) -> void {
  writer.Uint(unum);
}

auto JSONHelper::writeValue(Writer<StringBuffer>& writer, int num) -> void {
  writer.Int(num);
}

auto JSONHelper::writeValue(Writer<StringBuffer>& writer, bool b) -> void {
  writer.Bool(b);
}

auto JSONHelper::writeValue(Writer<StringBuffer>& writer, Event event) -> void {
  writer.StartObject();
  writePair(writer, "type", (unsigned int) event.type);
  writePair(writer, "player", event.player);
  writePair(writer, "piece", event.piece);
  writePair(writer, "decision", event.decision);
  writer.EndObject();
}

auto JSONHelper::writeValue(Writer<StringBuffer>& writer, Piece p) -> void {
  writer.Uint(p.raw_value());
}

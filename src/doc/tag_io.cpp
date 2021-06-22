// Aseprite Document Library
// Copyright (C) 2019  Igara Studio S.A.
// Copyright (C) 2001-2018  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "doc/tag_io.h"

#include "base/serialization.h"
#include "doc/string_io.h"
#include "doc/tag.h"

#include <iostream>
#include <memory>

namespace doc {

using namespace base::serialization;
using namespace base::serialization::little_endian;

void write_tag(std::ostream& os, const Tag* tag)
{
  std::string name = tag->name();

  write32(os, tag->id());
  write32(os, tag->fromFrame());
  write32(os, tag->toFrame());
  write32(os, tag->color());
  // 0th bit: oneShot, 1st to 7th bits: aniDir
  write8(os, ((char)tag->aniDir() & 0b01111111) | (tag->oneShot() ? 0b10000000 : 0b00000000));
  write_string(os, tag->name());
}

Tag* read_tag(std::istream& is, bool setId)
{
  ObjectId id = read32(is);
  frame_t from = read32(is);
  frame_t to = read32(is);
  color_t color = read32(is);
  auto aniDir_oneShot = read8(is); // 0th bit: oneShot, 1st to 7th bits: aniDir
  AniDir aniDir = (AniDir)(aniDir_oneShot & 0b01111111);
  bool oneShot = (aniDir_oneShot & 0b10000000) == 0b10000000;
  std::string name = read_string(is);

  std::unique_ptr<Tag> tag(new Tag(from, to));
  tag->setColor(color);
  tag->setAniDir(aniDir);
  tag->setName(name);
  tag->setOneShot(oneShot);
  if (setId)
    tag->setId(id);
  return tag.release();
}

}

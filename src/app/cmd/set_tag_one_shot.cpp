// Aseprite
// Copyright (C) 2021  Nejiya
// Copyright (C) 2019  Igara Studio S.A.
// Copyright (C) 2001-2015  David Capello
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/cmd/set_tag_one_shot.h"

#include "doc/tag.h"

namespace app {
namespace cmd {

SetTagOneShot::SetTagOneShot(doc::Tag* tag, bool oneShot)
  : WithTag(tag)
  , m_oldValue(tag->oneShot())
  , m_newValue(oneShot)
  
{
}

void SetTagOneShot::onExecute()
{
  tag()->setOneShot(m_newValue);
  tag()->incrementVersion();
}

void SetTagOneShot::onUndo()
{
  tag()->setOneShot(m_oldValue);
  tag()->incrementVersion();
}

} // namespace cmd
} // namespace app

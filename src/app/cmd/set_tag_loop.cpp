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

#include "app/cmd/set_tag_loop.h"

#include "doc/tag.h"

namespace app {
namespace cmd {

SetTagLoop::SetTagLoop(doc::Tag* tag, bool loop)
  : WithTag(tag)
  , m_oldValue(tag->loop())
  , m_newValue(loop)
  
{
}

void SetTagLoop::onExecute()
{
  tag()->setLoop(m_newValue);
  tag()->incrementVersion();
}

void SetTagLoop::onUndo()
{
  tag()->setLoop(m_oldValue);
  tag()->incrementVersion();
}

} // namespace cmd
} // namespace app

/* Copyright (c) 2018 Oliver Lau <oliver@ersatzworld.net>
 * All rights reserved. 
 */

#include "entropist.h"
#include <iostream>
#include <vector>
#include <Carbon/Carbon.h>


static CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon)
{
  Entropist *entropist = reinterpret_cast<Entropist*>(refcon);
  switch (type)
  {
    case kCGEventKeyUp:
    {
      CGKeyCode keycode = static_cast<CGKeyCode>(CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));
      CGEventFlags flags = static_cast<CGEventFlags>(CGEventGetFlags(event));
      CGEventTimestamp timestamp = CGEventGetTimestamp(event);
      entropist->add(reinterpret_cast<uint8_t*>(&timestamp), sizeof(timestamp));
      entropist->add(reinterpret_cast<uint8_t*>(&keycode), sizeof(keycode));
      entropist->add(reinterpret_cast<uint8_t*>(&flags), sizeof(flags));
      break;
    }
    case kCGEventMouseMoved:
    {
      CGPoint location = CGEventGetLocation(event);
      CGEventTimestamp timestamp = CGEventGetTimestamp(event);
      entropist->add(reinterpret_cast<uint8_t*>(&timestamp), sizeof(timestamp));
      entropist->add(reinterpret_cast<uint8_t*>(&location), sizeof(location));
      break;
    }
    default:
      break;
  }
  entropist->output();
  return event;
}


void Entropist::runner(void)
{
  const CGEventMask eventMask = 
    CGEventMaskBit(kCGEventMouseMoved) |
    CGEventMaskBit(kCGEventKeyUp);
  CFMachPortRef eventTap = CGEventTapCreate(
      kCGSessionEventTap,
      kCGHeadInsertEventTap,
      kCGEventTapOptionDefault,
      eventMask,
      eventCallback,
      &instance());
  if (!eventTap)
  {
      std::cerr << "failed to create event tap" << std::endl;
      return;
  }
  CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);
  if (eventTap) {
    CFRelease(eventTap);
  }
  if (runLoopSource) {
    CFRelease(runLoopSource);
  }
  CFRunLoopRun();
}

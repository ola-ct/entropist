// -*- coding: utf-8 -*-
// Copyright (c) 2018 Oliver Lau <oliver@ersatzworld.net>
// All rights reserved.


#ifndef __ENTROPY_H__
#define __ENTROPY_H__

#include <vector>
#include <stdint.h>
#include <sys/types.h>

double calcEntropyBits(const std::vector<uint8_t> &);

#endif

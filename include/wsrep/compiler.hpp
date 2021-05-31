/*
 * Copyright (C) 2018 Codership Oy <info@codership.com>
 *
 * This file is part of wsrep-lib.
 *
 * Wsrep-lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Wsrep-lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with wsrep-lib.  If not, see <https://www.gnu.org/licenses/>.
 */


/** @file compiler.hpp
 *
 * Compiler specific macro definitions.
 *
 * WSREP_WARN_UNUSED_RESULT - Mark function or methods so that a warning is
 *                            raised if its return value is unused.
 */

#define WSREP_UNUSED __attribute__((unused))
#if __cplusplus >= 201103L
#define WSREP_OVERRIDE override
#else
#define WSREP_OVERRIDE
#endif // __cplusplus >= 201103L

/* Fetched from https://github.com/codership/wsrep-lib/pull/123/ */
#define WSREP_WARN_UNUSED_RESULT __attribute__((warn_unused_result))

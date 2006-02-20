/**
 *  LibAxl:  Another XML library
 *  Copyright (C) 2006 Advanced Software Production Line, S.L.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1 of
 *  the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *  
 *  You may find a copy of the license under this software is released
 *  at COPYING file. This is LGPL software: you are welcome to
 *  develop proprietary applications using this library without any
 *  royalty or fee but returning back any change, improvement or
 *  addition in the form of source code, project image, documentation
 *  patches, etc. 
 *
 *  For commercial support on build XML enabled solutions contact us:
 *          
 *      Postal address:
 *         Advanced Software Production Line, S.L.
 *         C/ Dr. Michavila N� 14
 *         Coslada 28820 Madrid
 *         Spain
 *
 *      Email address:
 *         info@aspl.es - http://fact.aspl.es
 */
#ifndef __AXL_NODE_H__
#define __AXL_NODE_H__

#include <axl_decl.h>

BEGIN_C_DECLS

axlNode * axl_node_create             (char * name);

void      axl_node_set_child          (axlNode * parent, axlNode * child);

void      axl_node_set_is_empty       (axlNode * node, bool empty);

bool      axl_node_is_empty           (axlNode * node);

char    * axl_node_get_content        (axlNode * node, int * content_size);

char    * axl_node_get_content_copy   (axlNode * node, int * content_size);

void      axl_node_set_have_childs    (axlNode * node, bool childs);

bool      axl_node_have_childs        (axlNode * node);

void      axl_node_free            (axlNode * node);

END_C_DECLS

#endif

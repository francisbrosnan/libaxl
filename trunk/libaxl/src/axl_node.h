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

/** 
 * \addtogroup axl_node_module
 * @{
 */

axlNode * axl_node_create                   (char * name);

axlNode * axl_node_create_ref               (char * name);

typedef struct _axlNodeFactory axlNodeFactory;

axlNode * axl_node_create_from_factory      (char * name, 
					     axlNodeFactory * factory);

axlNode * axl_node_create_from_factory_ref  (char * name, 
					     axlNodeFactory * factory);

axlDoc  * axl_node_get_doc                  (axlNode * node);

void      axl_node_set_doc                  (axlNode * node, axlDoc * doc);

void      axl_node_set_attribute            (axlNode * node, char * attribute, char * value);

void      axl_node_set_attribute_ref        (axlNode * node, char * attribute, char * value);

bool      axl_node_has_attribute            (axlNode * node, char * attribute);

char    * axl_node_get_attribute_value      (axlNode * node, char * attribute);

char    * axl_node_get_attribute_value_copy (axlNode * node, char * attribute);

char    * axl_node_get_attribute_value_trans (axlNode * node, char * attribute);

/** 
 * @brief Allows to easily check that the given xml node (\ref
 * axlNode) have the provided name.
 *
 * This macro is provided as a convenience to check that a particular
 * node have a particular name. Check the documentation that this
 * macro is wrapping to get examples: \ref axl_node_get_name.
 * 
 * @param node The \ref axlNode where the name will be compared with
 * the provided value.
 *
 * @param name The name to compare.
 * 
 * @return AXL_TRUE if names are equal or AXL_FALSE if not.
 */
#define NODE_CMP_NAME(node,name) (axl_cmp ((node != NULL) ? axl_node_get_name(node) : "><", (name != NULL) ? name : "<>"))

char    * axl_node_get_name           (axlNode * node);

axlNode * axl_node_get_parent         (axlNode * node);

axlNode * axl_node_get_next           (axlNode * node);

void      axl_node_set_child          (axlNode * parent, 
				       axlNode * child);

void      axl_node_set_is_empty       (axlNode  * node, 
				       bool       empty);

bool      axl_node_is_empty           (axlNode * node);

char    * axl_node_get_content        (axlNode * node, 
				       int  * content_size);

char    * axl_node_get_content_copy   (axlNode * node, 
				       int  * content_size);

char    * axl_node_get_content_trans  (axlNode * node, 
				       int * content_size);

char    * axl_node_get_content_trim   (axlNode * node,
				       int * content_size);

void      axl_node_set_content        (axlNode * node, 
				       char * content, 
				       int content_size);

void      axl_node_set_content_ref    (axlNode * node, 
				       char * content, 
				       int content_size);

void      axl_node_set_cdata_content  (axlNode * node,
				       char * content,
				       int content_size);

void      axl_node_set_have_childs    (axlNode * node, bool     childs);

bool      axl_node_have_childs        (axlNode * node);

axlNode * axl_node_get_child_called   (axlNode * parent, char * name);

axlNode * axl_node_get_child_nth      (axlNode * parent, int position);

int       axl_node_get_child_num      (axlNode * parent);

axlList * axl_node_get_childs         (axlNode * node);

bool      axl_node_are_equal          (axlNode * node, axlNode * node2);

void      axl_node_add_pi_target            (axlNode * node, 
					     char * target, 
					     char * content);

bool      axl_node_has_pi_target            (axlNode * node, 
					     char * pi_target);

char    * axl_node_get_pi_target_content    (axlNode * node, 
					     char * pi_target);

axlList * axl_node_get_pi_target_list       (axlNode * node);

int       axl_node_get_flat_size            (axlNode * node);

int       axl_node_dump_at                  (axlNode * node,
					     char    * content,
					     int       desp);

void      axl_node_free            (axlNode * node);

axlNodeFactory * axl_node_factory_create  (int steps);

axlNode        * axl_node_factory_get     (axlNodeFactory * factory);

void             axl_node_factory_release (axlNodeFactory * factory, axlNode * node);

void             axl_node_factory_free    (axlNodeFactory * factory); 

/* @} */

END_C_DECLS

#endif



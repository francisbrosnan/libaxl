#include <axl.h>
#include <stdio.h>

/** 
 * @brief Test entity support (basic entity support).
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_18 (axlError ** error)
{
	axlDtd * dtd = NULL;
	char   * content;

	/* parse af-arch DTD */
	dtd = axl_dtd_parse_from_file ("channel.dtd", error);
	if (dtd == NULL)
		return false;

	/* lookup for entity definitions */
	if (axl_dtd_entity_exists (dtd, "TEST", GENERAL_ENTITY)) {
		axl_error_new (-1, "Expected to not find an entity value which was found (TEST)..", NULL, error);
		return false;
	}
	
	if (axl_dtd_entity_exists (dtd, "URI", GENERAL_ENTITY)) {
		axl_error_new (-1, "Expected to not find an entity value which was found (URI)..", NULL, error);
		return false;
	}
	
	/* lookup for entity definitions that are expected to be found */
	if (! axl_dtd_entity_exists (dtd, "URI", PARAMETER_ENTITY)) {
		axl_error_new (-1, "Expected to find an entity value which wasn't found (% URI)..", NULL, error);
		return false;
	}

	if (! axl_dtd_entity_exists (dtd, "LOCS", PARAMETER_ENTITY)) {
		axl_error_new (-1, "Expected to find an entity value which wasn' found (% LOCS)..", NULL, error);
		return false;
	}

	/* now get the content inside */
	content = axl_dtd_entity_value (dtd, "CHAN", PARAMETER_ENTITY);
	if (content == NULL) {
		axl_error_new (-1, "Expected to find parameter entity content for (% CHAN) but it wasn't found", NULL, error);
		return false;
	}
	
	if (! axl_cmp (content, "CDATA")) {
		axl_error_new (-1, "Expected to find parameter entity content for (% CHAN) it doesn't match", NULL, error);
		return false;	
	}

	/* free the dtd */
	axl_dtd_free (dtd);

	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_17 (axlError ** error) 
{
	axlDoc  * doc  = NULL;
	axlDtd  * dtd  = NULL;

	/* parse common DTD file */
	dtd = axl_dtd_parse_from_file ("xml-rpc.dtd", error);
	if (dtd == NULL)
		return false;

	/* parse a file that must not be valid */
	doc = axl_doc_parse_from_file ("test17.xdl", error);
	if (doc == NULL)
		return false;

	/* the following validation must fail */
	if (axl_dtd_validate (doc, dtd, error)) {
		axl_error_new (-1, "A validation was produced when expected a failure", NULL, error);
		return false;
	}

	/* because a failure was expected, release memory allocated by
	 * axl_error_new */
	axl_error_free (*error);

	/* free the document */
	axl_doc_free (doc);

	/* release DTD reference */
	axl_dtd_free (dtd);

	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_16 (axlError ** error) 
{
	axlDoc  * doc  = NULL;
	axlDtd  * dtd  = NULL;

	/* parse common DTD file */
	dtd = axl_dtd_parse_from_file ("xml-rpc.dtd", error);
	if (dtd == NULL)
		return false;

	/* parse a file that must not be valid */
	doc = axl_doc_parse_from_file ("test03.xdl", error);
	if (doc == NULL)
		return false;

	/* the following validation must fail */
	if (axl_dtd_validate (doc, dtd, error)) {
		axl_error_new (-1, "A validation was produced when expected a failure", NULL, error);
		return false;
	}

	/* because a failure was expected, release memory allocated by
	 * axl_error_new */
	axl_error_free (*error);

	/* free the document */
	axl_doc_free (doc);

	/* parse the next file that must be valid */
	doc = axl_doc_parse_from_file ("test04.xdl", error);
	if (doc == NULL)
		return false;

	/* the following validation should successed */
	if (! axl_dtd_validate (doc, dtd, error))
		return false;

	/* release the document */
	axl_doc_free (doc);
	
	/* release DTD reference */
	axl_dtd_free (dtd);

	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_15 (axlError ** error) 
{
	axlDoc  * doc  = NULL;
	axlDtd  * dtd  = NULL;

	/* parse common DTD file */
	dtd = axl_dtd_parse_from_file ("xml-rpc.dtd", error);
	if (dtd == NULL)
		return false;

	/* parse a file that must not be valid */
	doc = axl_doc_parse_from_file ("test01.xdl", error);
	if (doc == NULL)
		return false;

	/* the following validation must fail */
	if (axl_dtd_validate (doc, dtd, error)) {
		axl_error_new (-1, "A validation was produced when expected a failure", NULL, error);
		return false;
	}

	/* because a failure was expected, release memory allocated by
	 * axl_error_new */
	axl_error_free (*error);

	/* free the document */
	axl_doc_free (doc);

	/* parse the next file that must be valid */
	doc = axl_doc_parse_from_file ("test02.xdl", error);
	if (doc == NULL)
		return false;

	/* the following validation should successed */
	if (! axl_dtd_validate (doc, dtd, error))
		return false;

	/* release the document */
	axl_doc_free (doc);
	
	/* release DTD reference */
	axl_dtd_free (dtd);

	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_14 (axlError ** error) 
{
	axlDoc  * doc  = NULL;
	axlNode * node = NULL;
	
	char    * xml_document;
	char    * value;
	int       size = 0;
	int       document_size;
	

	/* create an emtpy document */
	doc = axl_doc_create ("1.0", NULL, false);

	/* create the root node */
	node = axl_node_create ("test");
	axl_node_set_content (node, "This is a test (') (\") (>) (<) (&), more data###", -1);
	
	axl_doc_set_root (doc, node);

	/* dump the document */
	axl_doc_dump (doc, &xml_document, &document_size);
	
	if (!axl_cmp ("<?xml version='1.0' ?><test>This is a test (&apos;) (&quot;) (&gt;) (&lt;) (&amp;), more data###</test>",
		      xml_document)) {
		axl_error_new (-1, "Found dump mismatch that shows entities are not handled properly", NULL, error);
		return false;
	}

	/* free memory dump */
	axl_free (xml_document);

	/* get the content translated */
	value = axl_node_get_content_copy (node, &size);

	if (size != 68) {
		axl_error_new (-1, "Found a document size mismatch while dumping entity content", NULL, error);
		return false;
	}
	
	/* free the content received */
	axl_free (value);

	/* get the content translated */
	value = axl_node_get_content_trans (node, &size);

	if (size != 48) {
		axl_error_new (-1, "Found a document size mismatch while dumping entity content (already translated)", NULL, error);
		return false;
	}

	/* check node content returned */
	if (!axl_cmp (value, "This is a test (\') (\") (>) (<) (&), more data###")) {
		axl_error_new (-1, "Found an string mismatch while checking a node content which was translated", NULL, error);
		return false;
	}

	/* free the content translated */
	axl_free (value);

	/* free document */
	axl_doc_free (doc);

	doc = axl_doc_parse ("<?xml version='1.0' ?><test></test>", 37, error);
	if (doc == NULL) {
		printf ("Expected to parse a document but it fails, error was: %s\n", axl_error_get (*error));
		return false;
	}

	/* get the content */
	node = axl_doc_get (doc, "/test");
	if (node == NULL) {
		axl_error_new (-1, "Expected to find a node reference not found (/test)\n", NULL, error);
		return false;		
	}

	/* get the content */
	size  = 11;
	value = axl_node_get_content (node, &size);
	if (size != 0) {
		axl_error_new (-1, "Expected to find a node content with 0 bytes but it 11 (/test)\n", NULL, error);
		return false;
	}

	/* get the content copy */
	size  = 13;
	value = axl_node_get_content_copy (node, &size);
	if (size != 0) {
		axl_error_new (-1, "Expected to find a node content with 0 bytes but it 13 (/test)\n", NULL, error);
		return false;
	}
	axl_free (value);

	/* get content copy trans */
	size  = 14;
	value = axl_node_get_content_trans (node, &size);
	if (size != 0) {
		axl_error_new (-1, "Expected to find a node content with 0 bytes but it 14 (/test)\n", NULL, error);
		return false;
	}
	axl_free (value);

	/* get content trimmed */
	size  = 15;
	value = axl_node_get_content_trim (node, &size);
	if (size != 0) {
		axl_error_new (-1, "Expected to find a node content with 0 bytes but it 15 (/test)\n", NULL, error);
		return false;
	}

	/* free the document */
	axl_doc_free (doc);

	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_13 (axlError ** error) 
{
	axlDoc * doc  = NULL;
	axlDoc * doc2 = NULL;
	char   * content;
	int      size;
	
	doc = axl_doc_parse_from_file ("test13.xml", error);
	if (doc == NULL)
		return false;

	/* dump xml document */
	axl_doc_dump (doc, &content, &size);

	doc2 = axl_doc_parse (content, size, error);
	if (doc2 == NULL)
		return false;

	/* check if both documents are equals */
	if (! axl_doc_are_equal (doc, doc2)) {
		printf ("xml document content (size: %d):\n%s", size, content);
		axl_error_new (-1, "Expected to dump an equivalent xml document, but found an error", NULL, error);
		return false;
	}

	/* free dump */
	axl_free (content);
	   
	/* free axl document */
	axl_doc_free (doc);

	/* free axl document */
	axl_doc_free (doc2);
	
	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_12 (axlError ** error) 
{
	axlDoc * doc = NULL;
	axlDtd * dtd = NULL;

	/* parse gmovil file (an af-arch xml chunk) */
	doc = axl_doc_parse_from_file ("channel.xml", error); 
	if (doc == NULL) 
		return false;

	/* parse af-arch DTD */
	dtd = axl_dtd_parse_from_file ("channel.dtd", error);
	if (dtd == NULL)
		return false;

	/* perform DTD validation */
	if (! axl_dtd_validate (doc, dtd, error)) {
		return false;
	}

	/* free doc reference */
	axl_doc_free (doc); 

	/* parse gmovil file (an af-arch xml chunk) */
	doc = axl_doc_parse_from_file ("channel2.xml", error); 
	if (doc == NULL) 
		return false;

	/* perform DTD validation */
	if (! axl_dtd_validate (doc, dtd, error)) {
		return false;
	}

	/* free doc reference */
	axl_doc_free (doc); 

	/* parse gmovil file (an af-arch xml chunk) */
	doc = axl_doc_parse_from_file ("channel3.xml", error); 
	if (doc == NULL) 
		return false;

	/* perform DTD validation */
	if (! axl_dtd_validate (doc, dtd, error)) {
		return false;
	}

	/* free doc reference */
	axl_doc_free (doc); 

	/* parse gmovil file (an af-arch xml chunk) */
	doc = axl_doc_parse_from_file ("channel4.xml", error); 
	if (doc == NULL) 
		return false;

	/* perform DTD validation */
	if (! axl_dtd_validate (doc, dtd, error)) {
		return false;
	}

	/* free doc reference */
	axl_doc_free (doc); 
	
	/* free dtd reference */
	axl_dtd_free (dtd);

	/* parse a BEEP greetins example */
	doc = axl_doc_parse_from_file ("channel5.xml", error);
	if (doc == NULL)
		return false;

	/* parse the TLS dtd file */
	dtd = axl_dtd_parse_from_file ("channel.dtd", error);
	if (dtd == NULL)
		return false;

	/* perform DTD validation */
	if (! axl_dtd_validate (doc, dtd, error)) {
		return false;
	}

	/* free doc reference */
	axl_doc_free (doc); 
	
	/* free dtd reference */
	axl_dtd_free (dtd);
	

	/* test end */
	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_11 (axlError ** error) 
{
	axlDoc * doc = NULL;
	axlDtd * dtd = NULL;

	/* parse gmovil file (an af-arch xml chunk) */
	doc = axl_doc_parse_from_file ("gmovil2.xml", error); 
	if (doc == NULL) 
		return false;

	/* parse af-arch DTD */
	dtd = axl_dtd_parse_from_file ("fact.dtd", error);
	if (dtd == NULL)
		return false;

	/* perform DTD validation */
	if (! axl_dtd_validate (doc, dtd, error)) {
		return false;
	}

	/* free doc reference */
	axl_doc_free (doc); 
	
	/* free dtd reference */
	axl_dtd_free (dtd);

	/* test end */
	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_10 (axlError ** error) 
{
	axlDoc                * doc      = NULL;
	axlDtd                * dtd      = NULL;
	axlDtdElement         * element  = NULL;
	axlDtdElementList     * itemList = NULL;

	/* parse gmovil file (an af-arch xml chunk) */
	doc = axl_doc_parse_from_file ("test5.xml", error); 
	if (doc == NULL) 
		return false;

	/* parse af-arch DTD */
	dtd = axl_dtd_parse_from_file ("test5.dtd", error);
	if (dtd == NULL)
		return false;

	/* get the dtd element representation */
	element = axl_dtd_get_element (dtd, "choices");

	/* get the item list inside */
	itemList = axl_dtd_get_item_list (element);
	if (axl_dtd_item_list_count (itemList) != 4) {
		axl_error_new (-1, "expected to receive an item list with 4 item nodes inside", NULL, error);
		return false;
	}

	if (axl_dtd_item_list_type (itemList) != CHOICE) {
		axl_error_new (-1, "expected to receive a choice item list", NULL, error);
		return false;
	}

	if (axl_dtd_item_list_repeat (itemList) != ZERO_OR_MANY) {
		axl_log ("test-01", AXL_LEVEL_DEBUG, "received a different repeat configuration: %d != %d",
			 ZERO_OR_MANY, axl_dtd_item_list_repeat (itemList));
		axl_error_new (-1, "expected to receive an item list with (*) zero or many spec", NULL, error);
		return false;
	}
	

	/* perform DTD validation */
	if (! axl_dtd_validate (doc, dtd, error)) { 
		return false; 
	} 

	/* free dtd reference */
	axl_dtd_free (dtd);


	/* parse af-arch DTD */
	dtd = axl_dtd_parse_from_file ("test5.1.dtd", error);
	if (dtd == NULL)
		return false;
	
	/* perform DTD validation */
	if (axl_dtd_validate (doc, dtd, error)) { 
		axl_error_new (-1, "A validation failure was expected.", NULL, error);
		return false; 
	} 

	/* because a failure was expected, release memory allocated by
	 * axl_error_new */
	axl_error_free (*error);
	
	/* free doc reference */
	axl_doc_free (doc); 
	
	/* free dtd reference */
	axl_dtd_free (dtd);

	/* test end */
	return true;
}

/** 
 * @brief A more complex DTD parsing example
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_09 (axlError ** error) 
{
	axlDoc                * doc      = NULL;
	axlDtd                * dtd      = NULL;
	axlDtdElement         * element  = NULL;
	axlDtdElementList     * itemList = NULL;
	axlDtdElementListNode * itemNode = NULL;
	

	/* parse gmovil file (an af-arch xml chunk) */
	doc = axl_doc_parse_from_file ("test4.xml", error); 
	if (doc == NULL) 
		return false;

	/* parse af-arch DTD */
	dtd = axl_dtd_parse_from_file ("test4.dtd", error);
	if (dtd == NULL)
		return false;

	
	/* get dtd element */
	element = axl_dtd_get_element (dtd, "nodes");
	if (element == NULL) {
		axl_error_new (-1, "unable to find expected DTD element", NULL, error);
		return false;
	}

	/* get the item list */
	itemList = axl_dtd_get_item_list (element);
	if (axl_dtd_item_list_count (itemList) != 8) {
		axl_log ("test-01", AXL_LEVEL_CRITICAL, "found item list size: %d != 8",
			 axl_dtd_item_list_count (itemList));
		axl_error_new (-1, "expected to find an item list definition with 8 elements", NULL, error);
		return false;
	}

	/* check <first> node spec */
	itemNode = axl_dtd_item_list_get_node (itemList, 0);
	if (axl_dtd_item_node_get_type (itemNode) != NODE) {
		axl_error_new (-1, "expected to find an item node definition, not found", NULL, error);
		return false;
	}
	
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "first")) {
		axl_error_new (-1, "expected to find an item node name (first) definition, not found", NULL, error);
		return false;
	}

	if (axl_dtd_item_node_get_repeat (itemNode) != ONE_OR_MANY) {
		axl_error_new (-1, "expected to find an item node definition with one or many repeat def (+), not found", NULL, error);
		return false;
	}

	/* check <second> node spec */
	itemNode = axl_dtd_item_list_get_node (itemList, 1);
	if (axl_dtd_item_node_get_type (itemNode) != NODE) {
		axl_error_new (-1, "expected to find an item node definition, not found", NULL, error);
		return false;
	}
	
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "second")) {
		axl_error_new (-1, "expected to find an item node name (second) definition, not found", NULL, error);
		return false;
	}

	if (axl_dtd_item_node_get_repeat (itemNode) != ONE_AND_ONLY_ONE) {
		axl_error_new (-1, "expected to find an item node definition with one and only one repeat def (), not found", NULL, error);
		return false;
	}

	/* check <third> node spec */
	itemNode = axl_dtd_item_list_get_node (itemList, 2);
	if (axl_dtd_item_node_get_type (itemNode) != NODE) {
		axl_error_new (-1, "expected to find an item node definition, not found", NULL, error);
		return false;
	}
	
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "third")) {
		axl_error_new (-1, "expected to find an item node name (third) definition, not found", NULL, error);
		return false;
	}

	if (axl_dtd_item_node_get_repeat (itemNode) != ZERO_OR_ONE) {
		axl_error_new (-1, "expected to find an item node definition with zero or one repeat def (?), not found", NULL, error);
		return false;
	}

	/* check <fourth> node spec */
	itemNode = axl_dtd_item_list_get_node (itemList, 3);
	if (axl_dtd_item_node_get_type (itemNode) != NODE) {
		axl_error_new (-1, "expected to find an item node definition, not found", NULL, error);
		return false;
	}
	
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "fourth")) {
		axl_error_new (-1, "expected to find an item node name (fourth) definition, not found", NULL, error);
		return false;
	}

	if (axl_dtd_item_node_get_repeat (itemNode) != ONE_AND_ONLY_ONE) {
		axl_error_new (-1, "expected to find an item node definition with one and only one repeat def (), not found", NULL, error);
		return false;
	}

	/* check <fifth> node spec */
	itemNode = axl_dtd_item_list_get_node (itemList, 4);
	if (axl_dtd_item_node_get_type (itemNode) != NODE) {
		axl_error_new (-1, "expected to find an item node definition, not found", NULL, error);
		return false;
	}
	
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "fifth")) {
		axl_error_new (-1, "expected to find an item node name (fifth) definition, not found", NULL, error);
		return false;
	}

	if (axl_dtd_item_node_get_repeat (itemNode) != ZERO_OR_MANY) {
		axl_error_new (-1, "expected to find an item node definition with zero to many repeat def (*), not found", NULL, error);
		return false;
	}

	/* check <fourth> node spec */
	itemNode = axl_dtd_item_list_get_node (itemList, 5);
	if (axl_dtd_item_node_get_type (itemNode) != NODE) {
		axl_error_new (-1, "expected to find an item node definition, not found", NULL, error);
		return false;
	}
	
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "fourth")) {
		axl_error_new (-1, "expected to find an item node name (fourth) definition, not found", NULL, error);
		return false;
	}

	if (axl_dtd_item_node_get_repeat (itemNode) != ZERO_OR_MANY) {
		axl_error_new (-1, "expected to find an item node definition with zero to many repeat def (*), not found", NULL, error);
		return false;
	}

	/* check repetition pattern for node spec 6 */
	itemNode = axl_dtd_item_list_get_node (itemList, 6);
	if (axl_dtd_item_node_get_type (itemNode) != ELEMENT_LIST) {
		axl_error_new (-1, "expected to find an item node definition, not found", NULL, error);
		return false;
	}
	
	if (axl_dtd_item_node_get_repeat (itemNode) != ZERO_OR_ONE) {
		axl_log ("test-01", AXL_LEVEL_DEBUG, "repeat configuration was different: %d != %d",
			 axl_dtd_item_node_get_repeat (itemNode), ZERO_OR_ONE);
		axl_error_new (-1, "expected to find an item node definition with zero or one repeat def (?), not found", NULL, error);
		return false;
	}

	/* check repetition pattern for node spec 7 */
	itemNode = axl_dtd_item_list_get_node (itemList, 7);
	if (axl_dtd_item_node_get_type (itemNode) != ELEMENT_LIST) {
		axl_error_new (-1, "expected to find an item node definition, not found", NULL, error);
		return false;
	}
	
	if (axl_dtd_item_node_get_repeat (itemNode) != ZERO_OR_MANY) {
		axl_log ("test-01", AXL_LEVEL_DEBUG, "repeat configuration was different: %d != %d",
			 axl_dtd_item_node_get_repeat (itemNode), ZERO_OR_MANY);
		axl_error_new (-1, "expected to find an item node definition with zero or one repeat def (*), not found", NULL, error);
		return false;
	}


	/* perform DTD validation */
	if (! axl_dtd_validate (doc, dtd, error)) { 
		return false; 
	} 

	/* free doc reference */
	axl_doc_free (doc); 
	
	/* free dtd reference */
	axl_dtd_free (dtd);

	/* test end */
	return true;
}

/** 
 * @brief Perform a loading for a large file.
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_08 (axlError ** error)
{
	/* top level definitions */
	axlDoc            * doc = NULL;

	/* get current doc reference */
	doc = axl_doc_parse_from_file ("large.xml", error);
	if (doc == NULL)
		return false;

	/* release the document */
	axl_doc_free (doc);

	return true;
}


/** 
 * @brief A bit more complex DTD parsing checkings
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_07 (axlError ** error)
{
	/* top level definitions */
	axlDoc            * doc = NULL;
	axlDtd            * dtd = NULL;

	/* get current doc reference */
	doc = axl_doc_parse_from_file ("test3.xml", error);
	if (doc == NULL)
		return false;

	/* load DTD */
	dtd = axl_dtd_parse_from_file ("test3.dtd", error);
	if (dtd == NULL)
		return false;

	/* validate the xml document */
	if (! axl_dtd_validate (doc, dtd, error)) {
		return  false;
	}
	
	
	/* free document */
	axl_doc_free (doc);

	/* free dtd document */
	axl_dtd_free (dtd);

	return true;
}

/** 
 * @brief A bit more complex DTD parsing checkings
 * 
 * @param error The optional axlError to be used to report errors.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_06 (axlError ** error)
{
	/* top level definitions */
	axlDoc            * doc = NULL;
	axlDtd            * dtd = NULL;

	/* dtd iteration variables */
	axlDtdElement         * element;
	axlDtdElementList     * itemList;
	axlDtdElementListNode * itemNode;
	
	/* get current doc reference */
	doc = axl_doc_parse_from_file ("test3.xml", error);
	if (doc == NULL)
		return false;

	/* load DTD */
	dtd = axl_dtd_parse_from_file ("test3.dtd", error);
	if (dtd == NULL)
		return false;

	/* get the DTD element reference and check it */
	element = axl_dtd_get_root (dtd);
	if (element == NULL) {
		axl_error_new (-1, "Expected to receive a root DTD node, not found", NULL, error);
		return false;
	}

	/* check expected DTD root content */
	if (! axl_cmp (axl_dtd_get_element_name (element), "complex")) {
		axl_error_new (-1, "Expected to receive a root DTD node name, not found", NULL, error);
		return false;
	}

	if (axl_dtd_get_element_type (element) != ELEMENT_TYPE_CHILDREN) {
		axl_error_new (-1, "Expected to receive a root DTD node selection type (Children), not found", NULL, error);
		return false;
	}

	/* get content specification */
	itemList = axl_dtd_get_item_list (element);
	if (axl_dtd_item_list_count (itemList) != 1) {
		axl_log ("test-01", AXL_LEVEL_DEBUG, "item count %d != %d item spected",
			 axl_dtd_item_list_count (itemList), 1);
		axl_error_new (-1, "Expected to receive an item list specification with only one node, not found", NULL, error);
		return false;
	}

	/* get times configuration */
	if (axl_dtd_item_list_repeat (itemList) != ONE_AND_ONLY_ONE) {
		axl_error_new (-1, "Expected to receive a repetition configuration (one and only one) but not found", NULL, error);
		return false;
	}

	/* get the child node reference */
	itemNode = axl_dtd_item_list_get_node (itemList, 0);
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "data")) {
		axl_log ("test-01", AXL_LEVEL_CRITICAL, "found item name: '%s' != data",
			 axl_dtd_item_node_get_value (itemNode));
		axl_error_new (-1, "Expected to receive an item node but, not found", NULL, error);
		return false;
	}

	/* get the DTD element which represents the provided data */
	element = axl_dtd_get_element (dtd, "data");
	if ((element == NULL) || (!axl_cmp (axl_dtd_get_element_name (element), "data"))) {
		axl_error_new (-1, "Expected to receive a DTD element definition but NULL was found or a different DTD name, not found", NULL, error);
		return false;
	}
	
	/* get content specification */
	itemList = axl_dtd_get_item_list (element);
	if (axl_dtd_item_list_count (itemList) != 3) {
		axl_log ("test-01", AXL_LEVEL_DEBUG, "item count %d != %d item spected",
			 axl_dtd_item_list_count (itemList), 3);
		axl_error_new (-1, "Expected to receive an item list specification with only one node, not found", NULL, error);
		return false;
	}

	/* get item list especification */
	if (axl_dtd_item_list_type (itemList) != SEQUENCE) {
		axl_log ("test-01", AXL_LEVEL_DEBUG, "item count %d != %d item spected",
			 axl_dtd_item_list_count (itemList), 3);
		axl_error_new (-1, "Expected to receive an item list specification as a sequence type, not found", NULL, error);
		return false;
	}

	/* check item nodes found inside the item list */
	itemNode = axl_dtd_item_list_get_node (itemList, 0);
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "row")) {
		axl_error_new (-1, "Expected to receive an item node (row) but, not found", NULL, error);
		return false;
	}

	/* get the child node reference */
	itemNode = axl_dtd_item_list_get_node (itemList, 1);
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "column")) {
		axl_error_new (-1, "Expected to receive an item node (column) but, not found", NULL, error);
		return false;
	}

	/* get current configuration for repetition value for the
	 * provided content particule */
	if (axl_dtd_item_node_get_repeat (itemNode) != ONE_AND_ONLY_ONE) {
		axl_error_new (-1, "Expected to receive an item node repeat configuration but, not found", NULL, error);
		return false;
	}
		

	/* get the child node reference */
	itemNode = axl_dtd_item_list_get_node (itemList, 2);
	if (! axl_cmp (axl_dtd_item_node_get_value (itemNode), "value")) {
		axl_error_new (-1, "Expected to receive an item node (value) but, not found", NULL, error);
		return false;
	}

	/* now work with the choice element */
	element = axl_dtd_get_element (dtd, "column");
	if ((element == NULL) || (!axl_cmp (axl_dtd_get_element_name (element), "column"))) {
		axl_error_new (-1, "Expected to receive a DTD element definition but NULL was found or a different DTD name (column), not found", NULL, error);
		return false;
	}
	
	/* get content specification */
	itemList = axl_dtd_get_item_list (element);
	if (axl_dtd_item_list_count (itemList) != 4) {
		axl_log ("test-01", AXL_LEVEL_DEBUG, "item count %d != %d item spected",
			 axl_dtd_item_list_count (itemList), 4);
		axl_error_new (-1, "Expected to receive an item list specification with only one node, not found", NULL, error);
		return false;
	}

	/* get item list especification */
	if (axl_dtd_item_list_type (itemList) != CHOICE) {
		axl_error_new (-1, "Expected to receive an item list specification as a CHOICE type, not found", NULL, error);
		return false;
	}

	/* get the DTD element which represents the provided data */
	element = axl_dtd_get_element (dtd, "data");
	if ((element == NULL) || (!axl_cmp (axl_dtd_get_element_name (element), "data"))) {
		axl_error_new (-1, "Expected to receive a DTD element definition but NULL was found or a different DTD name, not found", NULL, error);
		return false;
	}


	/* free document */
	axl_doc_free (doc);

	/* free dtd document */
	axl_dtd_free (dtd);

	return true;
}

/** 
 * @brief DTD operations. Checks that DTD support works, reading
 * simple DTD definitions, and ensuring elements are properly read.
 * 
 * @param error The axlError reference to be filled if the function
 * returns false.
 * 
 * @return true if the validity test is passed, false if not.
 */
bool test_05 (axlError ** error)
{

	axlDoc * doc;
	axlNode * node;
	axlDtd  * dtd;

	/* parse the document found */
	doc = axl_doc_parse_from_file ("test.xml", error);
	if (doc == NULL)
		return false;

	node = axl_doc_get (doc, "/complex/data/row/td");
	if (node == NULL) {
		axl_error_new (-1, "Expected to receive a node, not found", NULL, error);
		axl_doc_free (doc);
		return false;
	}

	if (! axl_cmp (axl_node_get_content (node, NULL), "10")) {
		axl_error_new (-1, "Expected to receive a node content, not found", NULL, error);
		axl_doc_free (doc);
		return false;
	}

	/* free previous document */
	axl_doc_free (doc);

	/* parse the document found */
	doc = axl_doc_parse_from_file ("test2.xml", error);
	if (doc == NULL)
		return false;
	
	
	dtd = axl_dtd_parse_from_file ("test.dtd", error);
	if (dtd == NULL)
		return false;

	/* now validate the document */
	if (! axl_dtd_validate (doc, dtd, error)) {
		return false;
	}

	/* release memory used by the parser */
	axl_doc_free (doc);
	
	/* release memory used by the DTD element */
	axl_dtd_free (dtd);

	return true;
	
}

/** 
 * @brief Perform some additional checks for a more extended xml
 * documents, that includes attributes inside node definitions.
 *
 * @param error The axlError where failures will be reported 
 *
 * @return The \ref true if test is passed, false if not.
 */
bool test_04 (axlError ** error)
{
	axlDoc  * doc;
	axlNode * node;

	/* parse the document */
	doc = axl_doc_parse_strings (error, 
				     "<?xml version='1.0' ?>",
				     "  <?test \"my content\" ?>",
				     "  <complex>",
				     "    <data>",
				     "       <row>",
				     "         <!-- A comment inside the middle of the document ",
				     " more comments ... ",
				     " more comments \n \r <td>..</td> -->",
				     "          <td>10</td>",
				     "          <test />",
				     " \n \n \r     <?test \"my content\" ?>     \n    \n",
				     "  <?test \"my content\" ?>",
				     "          <more>",
				     "              <test3 attr='2.0' />",
				     "          </more>",
				     "       </row>",
				     "       <test2 />",
				     "       <non-xml-document>",
				     "                             \n \r \n \t",
				     "         <![CDATA[<xml><<<<<<>>>>>><<<>>>><<<<<<>>>]]>"
				     "          \r \n \r \t",
				     "       </non-xml-document>",
				     "    </data>",
				     " <!--   <data>",
				     "       <row>",
				     "         A comment inside the middle of the document ",
				     " more comments ... ",
				     " more comments \n \r <td>..</td> ",
				     "          <td>10</td>",
				     "          <test />",
				     "          <more>",
				     "              <test2 attr='2.0' attr2='3.0' attr4='4.0'/>",
				     "          </more>",
				     "       </row>",
				     "       <test2 />",
				     "    </data> -->",
				     "  </complex>",
				     NULL);
	/* check the result returned */
	if (doc == NULL)
		return false;

	/* get the node <td> value */
	node = axl_doc_get (doc, "/complex/data/row/td");
	if (! axl_cmp (axl_node_get_content (node, NULL), "10")) {
		axl_log ("test-04", AXL_LEVEL_DEBUG, "found a different content than the expected ('10' != '%s')",
			 axl_node_get_content (node, NULL));
		axl_error_new (-1, "Expected to receive a 10 value, but not found", NULL, error);
		return false;
	}

	/* get a reference to the test2 node */
	node = axl_doc_get (doc, "/complex/data/row/more/test3");
	if (node == NULL) {
		axl_error_new (-1, "Expected to find a test3 node at the given location", NULL, error);
		return false;
	}

	/* check the attribute */
	if (! axl_node_has_attribute (node, "attr")) {
		axl_error_new (-1, "Expected to find an attribute called 'attr' inside test3 node at the given location", NULL, error);
		return false;
	}

	/* check the attribute value */
	if (! axl_cmp (axl_node_get_attribute_value (node, "attr"), "2.0")) {
		axl_error_new (-1, "Expected to find an attribute value equal '2.0' inside test2 node at the given location", NULL, error);
		return false;
	}

	/* add here Pi instruction checking */
	if (! axl_doc_has_pi_target (doc, "test")) {
		axl_error_new (-1, "failed to get expected PI target 'test'", NULL, error);
		return false;
	}

	if (! axl_cmp (axl_doc_get_pi_target_content (doc, "test"), "\"my content\"")) {
		axl_error_new (-1, "expected to receive a PI content not found", NULL, error);
		return false;
	}

	node = axl_doc_get (doc, "/complex/data/row");
	if (node == NULL) {
		axl_error_new (-1, "unable to get expected node to check node PI support", NULL, error);
		return false;
	}

	if (! axl_node_has_pi_target (node, "test")) {
		axl_error_new (-1, "failed to get expected PI target 'test' for the node", NULL, error);
		return false;
	}

	
	node = axl_doc_get (doc, "/complex/data/non-xml-document");
	if (node == NULL) {
		axl_error_new (-1, "Expected to receive the CDATA node, not found", NULL, error);
		return false;
	}

	if (! axl_cmp (axl_node_get_content (node, NULL), "<xml><<<<<<>>>>>><<<>>>><<<<<<>>>")) {
		printf ("Content doesn't match: %s != %s\n", 
			axl_node_get_content (node, NULL), "<xml><<<<<<>>>>>><<<>>>><<<<<<>>>");
		axl_error_new (-1, "Expected to recevie CDATA content, not found or not match", NULL, error);
		return false;
	}

				     
	/* free the memory */
	axl_doc_free (doc);
	
	return true;
}

/** 
 * @brief Checks a more extended and complex xml documents
 * 
 * @param error The axlError where failures will be reported.
 * 
 * @return \ref true if test is passed, false if not.
 */
bool test_03 (axlError ** error)
{

	axlDoc  * doc;
	axlNode * node;

	/* parse the xml document provided */
	doc = axl_doc_parse ("<?xml version='1.0' ?>\n\
<complex>\n\
  <data>\n\
    <row>10</row><row>20</row><row>30</row><row>40</row>\n\
  </data>\n\
  <data2>\n\
    <td> 23  </td>\n\
  </data2>\n\
</complex>", -1, error);
	if (doc == NULL)
		return false;

	/* get the root node */
	node = axl_doc_get_root (doc);
	if (! NODE_CMP_NAME (node, "complex")) {
		axl_error_new (-2, "Root node returned from the document is not the one excepted", NULL, error);
		axl_doc_free (doc);
		return false;
	}

	/* test get node function */
	node = axl_doc_get (doc, "/complex/data2/td");
	if (node == NULL) {
		axl_error_new (-2, "Unable to find a node due to a path selection", NULL, error);
		axl_doc_free (doc);
		return false;
	}

	/* check the node returned */
	if (! NODE_CMP_NAME (node, "td")) {
		axl_error_new (-2, "The node for the node looked up doesn't match ", NULL, error);
		axl_doc_free (doc);
		return false;
	}

	/* check for returning bad nodes */
	node = axl_doc_get (doc, "/complex/data3/td");
	if (node != NULL) {
		axl_error_new (-2, "Returned a node that should be NULL", NULL, error);
		axl_doc_free (doc);
		return false;
	}

	node = axl_doc_get (doc, "/complex/data2/td");
	if (!axl_cmp (axl_node_get_content (node, NULL), " 23  ")) {
		axl_log ("test-03", AXL_LEVEL_DEBUG, "expected to receive a node content: ' 23  ' but received '%s'",
			 axl_node_get_content (node, NULL));
		axl_error_new (-2, "Node content have failed, expected a different value", NULL, error);
		return false;
	}

	node = axl_doc_get (doc, "complex/data3/td");
	if (node != NULL) {
		axl_error_new (-2, "Parsed a path that is invalid", NULL, error);
		return false;
	}
	
	/* release memory allocated by the document */
	axl_doc_free (doc);

	return true;
}

/** 
 * @brief Checks xml document error for basic parsing.
 * 
 * @param error The axlError where failures are returned.
 * 
 * @return true if test are properly run. false if not.
 */
bool test_02 (axlError ** error) 
{
	axlDoc * doc;
	
	doc = axl_doc_parse ("<? xml >", 8, error);
	if (doc != NULL) {
		axl_error_new (-1, "Failed to detect wrong xml header", NULL, error);
		return false;
	}
	axl_error_free (* error);

	doc = axl_doc_parse ("<?xml >", 7, error);
	if (doc != NULL) {
		
		axl_error_new (-1, "Failed to detect wrong xml trailing header", NULL, error);
		return false;
	}
	axl_error_free (* error);


	return true;
}


/** 
 * @brief Parse an initial document, with an xml header with
 * version=1.0 and no more header.
 * 
 * 
 * @return false if the function fails to parse the
 * document. true if the test was properly executed.
 */
bool test_01 (axlError ** error) 
{
	/* axl document representation */
	axlDoc   * doc;
	

	/* parse the given string */
	doc = axl_doc_parse ("<?xml version='1.0' ?><axldoc />", 32, error);
	if (doc == NULL) {
		return false;
	}
	axl_doc_free (doc);

	doc = axl_doc_parse ("<?xml      version='1.0'            ?>      <another />", 55, error);
	if (doc == NULL) {
		return false;
	}
	
	/* release document parsed */
	axl_doc_free (doc);

	doc = axl_doc_parse ("<?xml    \n   \t \n \r version='1.0' ?>    <doc />", 50, error);
	if (doc == NULL) {
		return false;
	}

	/* release document parsed */
	axl_doc_free (doc);

	doc = axl_doc_parse ("<?xml  version=\"1.0\"        ?>   \r \t \n<another />", 54, error);
	if (doc == NULL) {
		return false;
	}

	/* release document parsed */
	axl_doc_free (doc);

	doc = axl_doc_parse ("<?xml  version=\"1.0\" \t \n \r encoding='utf-8\"   ?> <data />", 63, error);
	if (doc == NULL) {
		return false;
	}

	if (strcmp ("utf-8", axl_doc_get_encoding (doc))) {
		printf ("ERROR: encoding read from the document differs from the expected (got %s, expected %s)!\n",
			axl_doc_get_encoding (doc), "utf-8");
		return false;
	}

	/* release document parsed */
	axl_doc_free (doc);

	doc = axl_doc_parse ("<?xml version='1.0' encoding='utf-8' standalone='yes' ?>  <data/>", 65, error);
	if (doc == NULL) {
		return false;
	}

	if (!axl_doc_get_standalone (doc)) {
		printf ("ERROR: Expected to receive a true standalone configuration but false was found\n");
		return false;
	}

	/* release document parsed */
	axl_doc_free (doc);
	

	return true;
}

/** 
 * @brief Axl stream boundary checks.
 * 
 * 
 * @return false if the function fails to parse the
 * document. true if the test was properly executed.
 */
bool test_01a (axlError ** error) 
{
	axlStream * stream;
	char      * value;
	int         chunk_matched = -2;

	/* parse the string */
	stream = axl_stream_new ("customer", -1, NULL, -1, error);
	if (stream == NULL) 
		return false;

	/* get the value */
	value = axl_stream_get_until (stream, NULL, &chunk_matched, true, 2, "[", ".");
	if (value != NULL) {
		/* free the stream */
		axl_stream_free (stream);

		/* fill an error */
		axl_error_new (-1, "expected to find a null value while parsing content", NULL, error);
		
		return false;
	}

	if (chunk_matched != -1) {
		/* free the stream */
		axl_stream_free (stream);

		/* fill an error */
		axl_error_new (-1, "expected to chunk matched value equal to -1", NULL, error);
		
		return false;
	}

	/* free the stream */
	axl_stream_free (stream);

	return true;
}

/** 
 * Test01: Initial xml header checking.
 */
int main (int argc, char ** argv) 
{
	axlError * error;
	
	/* initialize axl library */
	if (! axl_init ()) {
		printf ("Unable to initialize Axl library\n");
		return -1;
	}

	if (test_01 (&error))
		printf ("Test 01: basic xml parsing [   OK   ]\n");
	else {
		printf ("Test 01: basic xml parsing [ FAILED ]\n  (code: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}

	if (test_01a (&error)) {
		printf ("Test 01-a: Axl Stream boundary checks [   OK   ]\n");
	} else {
		printf ("Test 01-a: Axl Stream boundary checks [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_02 (&error))
		printf ("Test 02: basic xml error detection [   OK   ]\n");
	else {
		printf ("Test 02: basic xml error detection [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_03 (&error))
		printf ("Test 03: complex xml error detection [   OK   ]\n");
	else {
		printf ("Test 03: complex xml error detection [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_04 (&error))
		printf ("Test 04: complex xml parsing [   OK   ]\n");
	else {
		printf ("Test 04: complex xml parsing [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_05 (&error))
		printf ("Test 05: DTD basic parsing [   OK   ]\n");
	else {
		printf ("Test 05: DTD basic parsing [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_06 (&error))
		printf ("Test 06: DTD basic parsing (2) [   OK   ]\n");
	else {
		printf ("Test 06: DTD basic parsing (2) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_07 (&error)) 
		printf ("Test 07: DTD validation (I) [   OK   ]\n");
	else {
		printf ("Test 07: DTD validation (I) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_08 (&error)) 
		printf ("Test 08: Large XML file loading [   OK   ]\n");
	else {
		printf ("Test 08: Large XML file loading [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	



	if (test_09 (&error)) 
		printf ("Test 09: Complex DTD validation [   OK   ]\n");
	else {
		printf ("Test 09: Complex DTD validation [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}


	if (test_10 (&error)) 
		printf ("Test 10: Complex DTD validation (II) [   OK   ]\n");
	else {
		printf ("Test 10: Complex DTD validation (II) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}

	if (test_11 (&error)) 
		printf ("Test 11: Complex DTD validation (III) [   OK   ]\n");
	else {
		printf ("Test 11: Complex DTD validation (III) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_12 (&error)) 
		printf ("Test 12: Complex DTD validation (IV) [   OK   ]\n");
	else {
		printf ("Test 12: Complex DTD validation (IV) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_13 (&error)) 
		printf ("Test 13: XML memory dumping [   OK   ]\n");
	else {
		printf ("Test 13: XML memory dumping [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_14 (&error)) {
		printf ("Test 14: quotation and escape sequences (&,',\",<,>) [   OK   ]\n");
	} else {
		printf ("Test 14: quotation and escape sequences (&,',\",<,>) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_15 (&error)) {
		printf ("Test 15: DTD validation fail checks (25/04/2006) [   OK   ]\n");
	} else {
		printf ("Test 15: DTD validation fail checks (25/04/2006) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	


	if (test_16 (&error)) {
		printf ("Test 16: DTD validation fail checks (03/05/2006) [   OK   ]\n");
	} else {
		printf ("Test 16: DTD validation fail checks (03/05/2006) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_17 (&error)) {
		printf ("Test 17: DTD validation fail checks (02/07/2006) [   OK   ]\n");
	} else {
		printf ("Test 17: DTD validation fail checks (02/07/2006) [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	if (test_18 (&error)) {
		printf ("Test 18: DTD ENTITY support [   OK   ]\n");
	} else {
		printf ("Test 18: DTD ENTITY support [ FAILED ]\n  (CODE: %d) %s\n",
			axl_error_get_code (error), axl_error_get (error));
		axl_error_free (error);
		return -1;
	}	

	/* cleanup axl library */
	axl_end ();
	return 0;
}

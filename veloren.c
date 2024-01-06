#include "config.h"
#include <epan/packet.h>

#define FOO_PORT 14004

static int proto_foo;
static dissector_handle_t foo_handle;

static int
dissect_foo(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree _U_, void *data _U_)
{
//    proto_tree_add_protocol_format(tree, proto_foo, tvb, 0, -1, "This is Hello version %s, a Wireshark postdissector plugin prototype", "ABC");
#if 1
    col_set_str(pinfo->cinfo, COL_PROTOCOL, "VLR");
    /* Clear the info column */
    col_clear(pinfo->cinfo,COL_INFO);

    proto_item *ti = proto_tree_add_item(tree, proto_foo, tvb, 0, -1, ENC_LITTLE_ENDIAN);
#endif
    return tvb_captured_length(tvb);
}

void
proto_register_foo(void)
{
    proto_foo = proto_register_protocol (
        "Veloren Protocol", /* name        */
        "VLR",          /* short name  */
        "vlr"           /* filter_name */
        );
    // foo_handle = create_dissector_handle(dissect_foo, proto_foo);
    // register_postdissector(foo_handle);
}

void
proto_reg_handoff_foo(void)
{

    foo_handle = create_dissector_handle(dissect_foo, proto_foo);
    dissector_add_uint_with_preference("tcp.port", FOO_PORT, foo_handle);
}

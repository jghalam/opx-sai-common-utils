/************************************************************************
* LEGALESE:   "Copyright (c) 2015, Dell Inc. All rights reserved."
*
* This source code is confidential, proprietary, and contains trade
* secrets that are the sole property of Dell Inc.
* Copy and/or distribution of this source code or disassembly or reverse
* engineering of the resultant object code are strictly forbidden without
* the written consent of Dell Inc.
*
************************************************************************/
/**
* @file sai_oid_utils.h
*
* @brief This file contains common utility APIs for handling SAI Unified
*        Object ID
*
*************************************************************************/
#ifndef __SAI_OID_UTILS_H__
#define __SAI_OID_UTILS_H__

#include "saitypes.h"
#include <stdint.h>

/** \defgroup SAIOIDUTILAPIS SAI - Object Id Utility APIs
 *   Contains Common Utility APIs for handling SAI Unified Object ID
 *  \{
 */

/*
 * SAI Unified Object Id (sai_object_id_t) bit encoding scheme
-------------------------------------------------------------------------
|  RESV  |      OBJ TYPE          |              OBJ ID                 |
|   (4)  |        (12)            |               (48)                  |
-------------------------------------------------------------------------

OBJ ID   - Represents the SAI NPU object id unique for the specific
           object type. Encoded as 48-bits value.

OBJ TYPE - Represents the SAI object type, encoded as 12-bits value. The
           different SAI object types are defined as in sai_object_type_t.

RESV     - Reserved 4-bits for future use, will be set to all 0.

*/

#define SAI_UOID_OBJ_TYPE_BITPOS     48
#define SAI_UOID_NPU_OBJ_ID_BITPOS   0

#define SAI_UOID_OBJ_TYPE_MASK       0xFFF000000000000
#define SAI_UOID_NPU_OBJ_ID_MASK     0x000FFFFFFFFFFFF

/**
 * @brief Switch Id type
 */
typedef uint32_t sai_switch_id_t;

typedef uint64_t sai_npu_object_id_t;

/**
 * @brief Create SAI unified object id.
 *
 * @param[in] type SAI object type.
 * @param[in] id SAI object id.
 * @return SAI unified object id encoding the object type and object id.
 */
static inline sai_object_id_t sai_uoid_create (sai_object_type_t type,
                                               sai_npu_object_id_t id)
{
    sai_object_id_t uoid = 0;

    uoid = ((((uoid | id) << SAI_UOID_NPU_OBJ_ID_BITPOS) & SAI_UOID_NPU_OBJ_ID_MASK) |
            (((uoid | type) << SAI_UOID_OBJ_TYPE_BITPOS) & SAI_UOID_OBJ_TYPE_MASK));

    return uoid;
}

/**
 * @brief Get SAI object id from the unified object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return SAI object id part from the unified object id is returned.
 */
static inline sai_npu_object_id_t sai_uoid_npu_obj_id_get (sai_object_id_t uoid)
{
    return ((uoid & SAI_UOID_NPU_OBJ_ID_MASK) >> SAI_UOID_NPU_OBJ_ID_BITPOS);
}

/**
 * @brief Check if the SAI object type is in the valid range or not.
 *
 * @param[in] obj_type SAI object type.
 * @return true if SAI object type is valid else false is returned.
 */
static inline bool sai_is_obj_type_valid (sai_object_type_t obj_type)
{
    return ((obj_type >= SAI_OBJECT_TYPE_PORT) &&
            (obj_type < SAI_OBJECT_TYPE_MAX));
}

/**
 * @brief Get SAI object type from the unified object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return SAI object type part from unified object id is returned if it is
 * valid else SAI_OBJECT_TYPE_NULL is returned.
 */
static inline sai_object_type_t sai_uoid_obj_type_get (sai_object_id_t uoid)
{
    sai_object_type_t  obj_type;

    obj_type = (sai_object_type_t) ((uoid & SAI_UOID_OBJ_TYPE_MASK) >>
                                    SAI_UOID_OBJ_TYPE_BITPOS);

    return (sai_is_obj_type_valid (obj_type)) ? obj_type : SAI_OBJECT_TYPE_NULL;
}

/**
 * @brief Check if the SAI object id is port object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if port object id else false is returned.
 */
static inline bool sai_is_obj_id_port (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_PORT);
}

/**
 * @brief Check if the SAI object id is LAG object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if LAG object id else false is returned.
 */
static inline bool sai_is_obj_id_lag (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_LAG);
}

/**
 * @brief Check if the SAI object id is Virtual Router object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if virtual router object id else false is returned.
 */
static inline bool sai_is_obj_id_vr (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_VIRTUAL_ROUTER);
}

/**
 * @brief Check if the SAI object id is Router Interface object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if router interface object id else false is returned.
 */
static inline bool sai_is_obj_id_rif (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_ROUTER_INTERFACE);
}

/**
 * @brief Check if the SAI object id is Next Hop object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if next hop object id else false is returned.
 */
static inline bool sai_is_obj_id_next_hop (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_NEXT_HOP);
}

/**
 * @brief Check if the SAI object id is Next Hop Group object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if next hop group object id else false is returned.
 */
static inline bool sai_is_obj_id_next_hop_group (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_NEXT_HOP_GROUP);
}

/**
 * @brief Check if the SAI object id is acl table object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if acl table object id else false is returned.
 */
static inline bool sai_is_obj_id_acl_table (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_ACL_TABLE);
}

/**
 * @brief Check if the SAI object id is acl table group object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if acl table group object id else false is returned.
 */
static inline bool sai_is_obj_id_acl_table_group (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_ACL_TABLE_GROUP);
}

/**
 * @brief Check if the SAI object id is acl entry object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if acl entry object id else false is returned.
 */
static inline bool sai_is_obj_id_acl_entry (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_ACL_ENTRY);
}

/**
 * @brief Check if the SAI object id is acl counter object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if acl counter object id else false is returned.
 */
static inline bool sai_is_obj_id_acl_counter (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_ACL_COUNTER);
}

/**
 * @brief Check if the SAI object id is mirror session object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if mirror session object id else false is returned.
 */
static inline bool sai_is_obj_id_mirror_session (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_MIRROR_SESSION);
}

/**
 * @brief Check if the SAI object id is samplepacket session object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if samplepacket session object id else false is returned.
 */
static inline bool sai_is_obj_id_samplepkt_session (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_SAMPLEPACKET);
}

/**
 * @brief Check if the SAI object id is STP instance object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if STP instance object id else false is returned.
 */
static inline bool sai_is_obj_id_stp_instance (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_STP);
}

/**
 * @brief Check if the SAI object id is hostif trap group object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if hostif trap group object id else false is returned.
 */
static inline bool sai_is_obj_id_hostif_trap_group (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_HOSTIF_TRAP_GROUP);
}

/**
 * @brief Check if the SAI object id is Queue object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if queue object id else false is returned.
 */
static inline bool sai_is_obj_id_queue (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_QUEUE);
}

/**
 * @brief Check if the SAI object id is Qos Maps object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if qos maps object id else false is returned.
 */
static inline bool sai_is_obj_id_qos_map (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_QOS_MAP);
}

/**
 * @brief Check if the SAI object id is Qos Policer object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if policer object id else false is returned.
 */
static inline bool sai_is_obj_id_policer (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_POLICER);
}

/**
 * @brief Check if the SAI object id is Qos WRED object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if WRED object id else false is returned.
 */
static inline bool sai_is_obj_id_wred (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_WRED);
}

/**
 * @brief Check if the SAI object id is Qos Scheduler object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if Scheduler object id else false is returned.
 */
static inline bool sai_is_obj_id_scheduler (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_SCHEDULER);
}

/**
 * @brief Check if the SAI object id is Qos Scheduler group object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if Scheduler group object id else false is returned.
 */
static inline bool sai_is_obj_id_scheduler_group (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_SCHEDULER_GROUP);
}

/**
 * @brief Check if the SAI object id is UDF Group object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if UDF Group object id else false is returned.
 */
static inline bool sai_is_obj_id_udf_group (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_UDF_GROUP);
}

/**
 * @brief Check if the SAI object id is UDF Match object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if UDF object id else false is returned.
 */
static inline bool sai_is_obj_id_udf_match (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_UDF_MATCH);
}

/**
 * @brief Check if the SAI object id is UDF object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if UDF object id else false is returned.
 */
static inline bool sai_is_obj_id_udf (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_UDF);
}

/**
 * @brief Check if the SAI object id is Hash object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if Hash object id else false is returned.
 */
static inline bool sai_is_obj_id_hash (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_HASH);
}

/**
 * @brief Check if the SAI object id is Tunnel object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if Hash object id else false is returned.
 */
static inline bool sai_is_obj_id_tunnel (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_TUNNEL);
}

/**
 * @brief Check if the SAI object id is Tunnel map object id.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if Hash object id else false is returned.
 */
static inline bool sai_is_obj_id_tunnel_map (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_TUNNEL_MAP);
}

/**
 * @brief Check if the SAI object id is Tunnel termination table entry.
 *
 * @param[in] uoid SAI unified object id.
 * @return true if Hash object id else false is returned.
 */
static inline bool sai_is_obj_id_tunnel_term_entry (sai_object_id_t uoid)
{
    return (sai_uoid_obj_type_get (uoid) == SAI_OBJECT_TYPE_TUNNEL_TERM_TABLE_ENTRY);
}

/**
 * \}
 */

#endif

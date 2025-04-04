﻿/*++

Copyright (c) 2000-2001  Microsoft Corporation

Module Name:

    nldef.h

Abstract:

    This module contains basic network layer definitions.
    Previously some of these were duplicated in both routprot.h and
    iprtrmib.h.

Author:
Environment:

    user mode or kernel mode

--*/

#ifndef _NLDEF_
#pragma option push -b -a8 -pc -A- -w-pun /*P_O_Push*/
#define _NLDEF_
#pragma once
#include <winapifamily.h>

#pragma region Application Family or OneCore Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP | WINAPI_PARTITION_SYSTEM)


typedef enum {
    //
    // These values are from iptypes.h.
    // They need to fit in a 4 bit field.
    //
    IpPrefixOriginOther = 0,
    IpPrefixOriginManual,
    IpPrefixOriginWellKnown,
    IpPrefixOriginDhcp,
    IpPrefixOriginRouterAdvertisement,
    IpPrefixOriginUnchanged = 1 << 4
} NL_PREFIX_ORIGIN;

//
// TODO: Remove these definitions.
//
#define NlpoOther               IpPrefixOriginOther
#define NlpoManual              IpPrefixOriginManual
#define NlpoWellKnown           IpPrefixOriginWellKnown
#define NlpoDhcp                IpPrefixOriginDhcp
#define NlpoRouterAdvertisement IpPrefixOriginRouterAdvertisement

typedef enum {
    //
    // TODO: Remove the Nlso* definitions.
    //
    NlsoOther = 0,
    NlsoManual,
    NlsoWellKnown,
    NlsoDhcp,
    NlsoLinkLayerAddress,
    NlsoRandom,

    //
    // These values are from in iptypes.h.
    // They need to fit in a 4 bit field.
    //
    IpSuffixOriginOther = 0,
    IpSuffixOriginManual,
    IpSuffixOriginWellKnown,
    IpSuffixOriginDhcp,
    IpSuffixOriginLinkLayerAddress,
    IpSuffixOriginRandom,
    IpSuffixOriginUnchanged = 1 << 4
} NL_SUFFIX_ORIGIN;

typedef enum {
    //
    // TODO: Remove the Nlds* definitions.
    //
    NldsInvalid,
    NldsTentative,
    NldsDuplicate,
    NldsDeprecated,
    NldsPreferred,

    //
    // These values are from in iptypes.h.
    //
    IpDadStateInvalid    = 0,
    IpDadStateTentative,
    IpDadStateDuplicate,
    IpDadStateDeprecated,
    IpDadStatePreferred,
} NL_DAD_STATE;


#define NL_MAX_METRIC_COMPONENT ((((ULONG) 1) << 31) - 1)

//
// MIB_IPPROTO_* values were previously in iprtrmib.h.
// PROTO_IP_* values were previously in routprot.h.
//
#define MAKE_ROUTE_PROTOCOL(suffix, value) \
    MIB_IPPROTO_ ## suffix = value, \
    PROTO_IP_ ## suffix    = value

//
// Routing protocol values from RFC.
//
typedef enum {
    //
    // TODO: Remove the RouteProtocol* definitions.
    //
    RouteProtocolOther   = 1,
    RouteProtocolLocal   = 2,
    RouteProtocolNetMgmt = 3,
    RouteProtocolIcmp    = 4,
    RouteProtocolEgp     = 5,
    RouteProtocolGgp     = 6,
    RouteProtocolHello   = 7,
    RouteProtocolRip     = 8,
    RouteProtocolIsIs    = 9,
    RouteProtocolEsIs    = 10,
    RouteProtocolCisco   = 11,
    RouteProtocolBbn     = 12,
    RouteProtocolOspf    = 13,
    RouteProtocolBgp     = 14,
    RouteProtocolIdpr    = 15,
    RouteProtocolEigrp   = 16,
    RouteProtocolDvmrp   = 17,
    RouteProtocolRpl     = 18,
    RouteProtocolDhcp    = 19,

    MAKE_ROUTE_PROTOCOL(OTHER,   1),
    MAKE_ROUTE_PROTOCOL(LOCAL,   2),
    MAKE_ROUTE_PROTOCOL(NETMGMT, 3),
    MAKE_ROUTE_PROTOCOL(ICMP,    4),
    MAKE_ROUTE_PROTOCOL(EGP,     5),
    MAKE_ROUTE_PROTOCOL(GGP,     6),
    MAKE_ROUTE_PROTOCOL(HELLO,   7),
    MAKE_ROUTE_PROTOCOL(RIP,     8),
    MAKE_ROUTE_PROTOCOL(IS_IS,   9),
    MAKE_ROUTE_PROTOCOL(ES_IS,  10),
    MAKE_ROUTE_PROTOCOL(CISCO,  11),
    MAKE_ROUTE_PROTOCOL(BBN,    12),
    MAKE_ROUTE_PROTOCOL(OSPF,   13),
    MAKE_ROUTE_PROTOCOL(BGP,    14),
    MAKE_ROUTE_PROTOCOL(IDPR,   15),
    MAKE_ROUTE_PROTOCOL(EIGRP,  16),
    MAKE_ROUTE_PROTOCOL(DVMRP,  17),
    MAKE_ROUTE_PROTOCOL(RPL,    18),
    MAKE_ROUTE_PROTOCOL(DHCP,   19),

    //
    // Windows-specific definitions.
    //
    MAKE_ROUTE_PROTOCOL(NT_AUTOSTATIC,     10002),
    MAKE_ROUTE_PROTOCOL(NT_STATIC,         10006),
    MAKE_ROUTE_PROTOCOL(NT_STATIC_NON_DOD, 10007),

} NL_ROUTE_PROTOCOL, *PNL_ROUTE_PROTOCOL;

typedef enum {
    NlatUnspecified,
    NlatUnicast,
    NlatAnycast,
    NlatMulticast,
    NlatBroadcast,
    NlatInvalid
} NL_ADDRESS_TYPE, *PNL_ADDRESS_TYPE;

//
// NL_ROUTE_ORIGIN
//
// Define route origin values.
//

typedef enum _NL_ROUTE_ORIGIN {
    NlroManual,
    NlroWellKnown,
    NlroDHCP,
    NlroRouterAdvertisement,
    Nlro6to4,
} NL_ROUTE_ORIGIN, *PNL_ROUTE_ORIGIN;

//
// NL_NEIGHBOR_STATE
//
// Define network layer neighbor state.  RFC 2461, section 7.3.2 has details.
// Note: Only state names are documented, we chose the values used here.
//

typedef enum _NL_NEIGHBOR_STATE {
    NlnsUnreachable,
    NlnsIncomplete,
    NlnsProbe,
    NlnsDelay,
    NlnsStale,
    NlnsReachable,
    NlnsPermanent,
    NlnsMaximum,
} NL_NEIGHBOR_STATE, *PNL_NEIGHBOR_STATE;

typedef enum _NL_LINK_LOCAL_ADDRESS_BEHAVIOR{
    LinkLocalAlwaysOff = 0,     // Never use link locals.
    LinkLocalDelayed,           // Use link locals only if no other addresses.
                                // (default for IPv4).
                                // Legacy mapping: IPAutoconfigurationEnabled.
    LinkLocalAlwaysOn,          // Always use link locals (default for IPv6).
    LinkLocalUnchanged = -1
} NL_LINK_LOCAL_ADDRESS_BEHAVIOR;

#pragma warning(push)
#pragma warning(disable:4214)

typedef struct _NL_INTERFACE_OFFLOAD_ROD {
    BOOLEAN NlChecksumSupported : 1;
    BOOLEAN NlOptionsSupported : 1;
    BOOLEAN TlDatagramChecksumSupported : 1;
    BOOLEAN TlStreamChecksumSupported : 1;
    BOOLEAN TlStreamOptionsSupported : 1;
    BOOLEAN FastPathCompatible : 1;
    BOOLEAN TlLargeSendOffloadSupported : 1;
    BOOLEAN TlGiantSendOffloadSupported : 1;
} NL_INTERFACE_OFFLOAD_ROD, *PNL_INTERFACE_OFFLOAD_ROD;

#pragma warning(pop)

typedef enum _NL_ROUTER_DISCOVERY_BEHAVIOR {
    RouterDiscoveryDisabled = 0,
    RouterDiscoveryEnabled,
    RouterDiscoveryDhcp,
    RouterDiscoveryUnchanged = -1
} NL_ROUTER_DISCOVERY_BEHAVIOR;

typedef enum _NL_BANDWIDTH_FLAG {
    NlbwDisabled = 0,
    NlbwEnabled,
    NlbwUnchanged = -1
} NL_BANDWIDTH_FLAG, *PNL_BANDWIDTH_FLAG;

typedef struct _NL_PATH_BANDWIDTH_ROD {
    ULONG64 Bandwidth;
    ULONG64 Instability;
    BOOLEAN BandwidthPeaked;
} NL_PATH_BANDWIDTH_ROD, *PNL_PATH_BANDWIDTH_ROD;

typedef enum _NL_NETWORK_CATEGORY {
    NetworkCategoryPublic,
    NetworkCategoryPrivate,
    NetworkCategoryDomainAuthenticated,
    NetworkCategoryUnchanged = -1,          // used in a set operation
    NetworkCategoryUnknown = -1             // returned in a query operation
} NL_NETWORK_CATEGORY, *PNL_NETWORK_CATEGORY;

typedef enum _NL_INTERFACE_NETWORK_CATEGORY_STATE {
    NlincCategoryUnknown = 0,
    NlincPublic = 1,
    NlincPrivate = 2,
    NlincDomainAuthenticated = 3,
    NlincCategoryStateMax
} NL_INTERFACE_NETWORK_CATEGORY_STATE,
*PNL_INTERFACE_NETWORK_CATEGORY_STATE;

#define NET_IF_CURRENT_SESSION ((ULONG)-1)

typedef struct _NL_BANDWIDTH_INFORMATION {
    ULONG64 Bandwidth;
    ULONG64 Instability;
    BOOLEAN BandwidthPeaked;
} NL_BANDWIDTH_INFORMATION, *PNL_BANDWIDTH_INFORMATION;

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP | WINAPI_PARTITION_SYSTEM) */
#pragma endregion

#pragma option pop /*P_O_Pop*/
#endif // _NLDEF_


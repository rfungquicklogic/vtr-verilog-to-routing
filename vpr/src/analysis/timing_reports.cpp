#include "timing_reports.h"

#include "vtr_log.h"

#include "tatum/TimingReporter.hpp"

#include "vpr_types.h"
#include "globals.h"

#include "timing_info.h"
#include "timing_util.h"

#include "VprTimingGraphNameResolver.h"

void generate_setup_timing_stats(const SetupTimingInfo& timing_info) {
#ifdef ENABLE_CLASSIC_VPR_STA
    vtr::printf("\n");
    vtr::printf("New Timing Stats\n");
    vtr::printf("================\n");
#endif

    auto& timing_ctx = g_vpr_ctx.timing();
    auto& atom_ctx = g_vpr_ctx.atom();

    print_setup_timing_summary(*timing_ctx.constraints, *timing_info.setup_analyzer());

    VprTimingGraphNameResolver name_resolver(atom_ctx.nlist, atom_ctx.lookup);
    tatum::TimingReporter timing_reporter(name_resolver, *timing_ctx.graph, *timing_ctx.constraints);

    timing_reporter.report_timing_setup("report_timing.setup.rpt", *timing_info.setup_analyzer());
    timing_reporter.report_unconstrained_setup("report_unconstrained_timing.setup.rpt", *timing_info.setup_analyzer());
}

void generate_hold_timing_stats(const HoldTimingInfo& timing_info) {
    auto& timing_ctx = g_vpr_ctx.timing();
    auto& atom_ctx = g_vpr_ctx.atom();

    print_hold_timing_summary(*timing_ctx.constraints, *timing_info.hold_analyzer());

    VprTimingGraphNameResolver name_resolver(atom_ctx.nlist, atom_ctx.lookup);
    tatum::TimingReporter timing_reporter(name_resolver, *timing_ctx.graph, *timing_ctx.constraints);

    timing_reporter.report_timing_hold("report_timing.hold.rpt", *timing_info.hold_analyzer());
    timing_reporter.report_unconstrained_hold("report_unconstrained_timing.hold.rpt", *timing_info.hold_analyzer());
}
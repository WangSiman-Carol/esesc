/*****************************************************************************
 *                                McPAT
 *                      SOFTWARE LICENSE AGREEMENT
 *            Copyright 2009 Hewlett-Packard Development Company, L.P.
 *                          All Rights Reserved
 *
 * Permission to use, copy, and modify this software and its documentation is
 * hereby granted only under the following terms and conditions.  Both the
 * above copyright notice and this permission notice must appear in all copies
 * of the software, derivative works or modified versions, and any portions
 * thereof, and both notices must appear in supporting documentation.
 *
 * Any User of the software ("User"), by accessing and using it, agrees to the
 * terms and conditions set forth herein, and hereby grants back to Hewlett-
 * Packard Development Company, L.P. and its affiliated companies ("HP") a
 * non-exclusive, unrestricted, royalty-free right and license to copy,
 * modify, distribute copies, create derivate works and publicly display and
 * use, any changes, modifications, enhancements or extensions made to the
 * software by User, including but not limited to those affording
 * compatibility with other hardware or software, but excluding pre-existing
 * software applications that may incorporate the software.  User further
 * agrees to use its best efforts to inform HP of any such changes,
 * modifications, enhancements or extensions.
 *
 * Correspondence should be provided to HP at:
 *
 * Director of Intellectual Property Licensing
 * Office of Strategy and Technology
 * Hewlett-Packard Company
 * 1501 Page Mill Road
 * Palo Alto, California  94304
 *
 * The software may be further distributed by User (but not offered for
 * sale or transferred for compensation) to third parties, under the
 * condition that such third parties agree to abide by the terms and
 * conditions of this license.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" WITH ANY AND ALL ERRORS AND DEFECTS
 * AND USER ACKNOWLEDGES THAT THE SOFTWARE MAY CONTAIN ERRORS AND DEFECTS.
 * HP DISCLAIMS ALL WARRANTIES WITH REGARD TO THE SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL
 * HP BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE SOFTWARE.
 *
 ***************************************************************************/
#ifndef LOGIC_H_
#define LOGIC_H_

#include "XML_Parse.h"
#include "basic_components.h"
#include "cacti_interface.h"
#include "component.h"
#include "const.h"
#include "parameter.h"
#include "xmlParser.h"
#include <string.h>

using namespace std;

class selection_logic : public Component {
public:
  selection_logic(bool _is_default, int win_entries_, int issue_width_,
                  const InputParameter *configure_interface); //, const ParseXML *_XML_interface);
  bool            is_default;
  InputParameter  l_ip;
  uca_org_t       local_result;
  const ParseXML *XML_interface;
  int             win_entries;
  int             issue_width;
  int             num_threads;

  void selection_power();
};

class dep_resource_conflict_check : public Component {
public:
  dep_resource_conflict_check(const InputParameter *configure_interface, const CoreDynParam &dyn_p_, int compare_bits_,
                              bool _is_default = true);
  InputParameter l_ip;
  uca_org_t      local_result;
  double         WNORn, WNORp, Wevalinvp, Wevalinvn, Wcompn, Wcompp, Wcomppreequ;
  CoreDynParam   coredynp;
  int            compare_bits;
  bool           is_default;
  statsDef       tdp_stats;
  statsDef       rtp_stats;
  statsDef       stats_t;
  powerDef       power_t;

  void   conflict_check_power();
  double compare_cap();
};

class DFFCell : public Component {
public:
  DFFCell(bool _is_dram, double _WdecNANDn, double _WdecNANDp, double _cell_load, const InputParameter *configure_interface);
  InputParameter l_ip;
  bool           is_dram;
  double         cell_load;
  double         WdecNANDn;
  double         WdecNANDp;
  double         clock_cap;
  int            model;
  int            n_switch;
  int            n_keep_1;
  int            n_keep_0;
  int            n_clock;
  powerDef       e_switch;
  powerDef       e_keep_1;
  powerDef       e_keep_0;
  powerDef       e_clock;

  double fpfp_node_cap(unsigned int fan_in, unsigned int fan_out);
  void   compute_DFF_cell(void);
};

class PipelinePower : public Component {
public:
  PipelinePower(const InputParameter *configure_interface, const CoreDynParam &dyn_p_, bool _is_core_pipeline = true,
                bool _is_default = true);
  InputParameter l_ip;
  uca_org_t      local_result;
  CoreDynParam   coredynp;
  bool           is_core_pipeline, is_default;
  double         num_piperegs;
  //	int pipeline_stages;
  //	int tot_stage_vector, per_stage_vector;
  bool   process_ind;
  double WNANDn;
  double WNANDp;
  double load_per_pipeline_stage;
  //	int  Hthread,  num_thread, fetchWidth, decodeWidth, issueWidth, commitWidth, instruction_length;
  //	int  PC_width, opcode_length, num_arch_reg_tag, data_width,num_phsical_reg_tag, address_width;
  //	bool thread_clock_gated;
  //	bool in_order, multithreaded;
  void compute_stage_vector();
  void compute();
  ~PipelinePower(){};
};

// class core_pipeline :public pipeline{
// public:
//	int  Hthread,  num_thread, fetchWidth, decodeWidth, issueWidth, commitWidth, instruction_length;
//	int  PC_width, opcode_length, num_arch_reg_tag, data_width,num_phsical_reg_tag, address_width;
//	bool thread_clock_gated;
//	bool in_order, multithreaded;
//	core_pipeline(bool _is_default, const InputParameter *configure_interface);
//	virtual void compute_stage_vector();
//
//};

class FunctionalUnit : public Component {
public:
  FunctionalUnit(const InputParameter *configure_interface, enum FU_type fu_type, int n_fu, bool _is_default = true);
  InputParameter  l_ip;
  uca_org_t       local_result;
  const ParseXML *XML_interface;
  double          num_fu, FU_height;
  bool            is_default;

  bool exist;
};

class UndiffCore : public Component {
public:
  UndiffCore(const InputParameter *configure_interface, enum Core_type core_ty_, double pipeline_stage_, double num_hthreads_,
             double issue_width_, bool embedded_ = false, bool _is_default = true);
  InputParameter  l_ip;
  uca_org_t       local_result;
  const ParseXML *XML_interface;
  enum Core_type  core_ty;
  double          pipeline_stage, num_hthreads, issue_width;
  bool            opt_performance, embedded;
  bool            is_default;
};
#endif /* LOGIC_H_ */

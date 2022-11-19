/**
 * @file pipeline.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief The main pipeline, manage all resources.
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __SERVER_PIPELINE_HPP_
#define __SERVER_PIPELINE_HPP_

#ifdef _WIN32
#if _MSC_VER > 1000
#pragma once
#endif
#endif  //! _WIN32

#if defined(__unix__) && defined(__clang__)
#pragma once
#endif  //! defined(__unix__) && defined(__clang__)

#include <workflow/WFGraphTask.h>
#include <workflow/WFTaskFactory.h>

#include "cbWebserver.hpp"
#include "cbRestfulHttpServer.hpp"
#include "task/cbComputeGraph.hpp"
#include "trivial/cbVirtualDevice.hpp"

namespace cb {
namespace pipeline {

class graphContainer {
 public:
  ~graphContainer();
  graphContainer(int32_t n);
  graphContainer(graphContainer&) = delete;
  graphContainer(const graphContainer&) = delete;
  graphContainer operator=(graphContainer&) = delete;
  graphContainer operator=(const graphContainer&) = delete;

  void addGraph(graph::cbComputeGraph* g);
  void execMain();

 private:
  std::vector<graph::cbComputeGraph*> m_graphs;
  int32_t m_loopTime = 10;  ///! nano seconds.
};

struct appCfg {
  unsigned short webPort;
  char* webRoot;
  unsigned short rHttpPort;
  int32_t graphExecSec;
};

class app {
 public:
  app(const appCfg& cfg);

  /**
   * @brief
   *
   */
  void initRHttp();

  /**
   * @brief
   *
   */
  void execMain();

  /**
   * @brief
   *
   */
  void stopMain();

 private:
  graphContainer m_graphs;
  utils::cbWebserver m_web;
  utils::cbRestfulHttpServer m_rHttp;
  trivial::cbVirtualDeviceManager m_VDM;
};

}  // namespace pipeline
}  // namespace cb

#endif
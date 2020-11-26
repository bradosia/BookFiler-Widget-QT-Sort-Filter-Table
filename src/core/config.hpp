/*
 * @name BookFiler Library - Sort Filter Tree Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief Super fast tree sorting and filtering tree widget.
 */

#ifndef BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_CONFIG_H
#define BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_CONFIG_H

#define BOOKFILER_DEBUG 0
#define TREE_MODEL_DEBUG 1

// C++
#include <string>

/* boost 1.72.0
 * License: Boost Software License (similar to BSD and MIT)
 */
#define BOOST_ALLOW_DEPRECATED_HEADERS

namespace bookfiler {
namespace widget {

static std::string moduleName = "BookFiler Widget";
static std::string moduleCode = "bookfiler::widget";

} // namespace widget
} // namespace bookfiler

#endif // BOOKFILER_MODULE_SSH_CONFIG_H

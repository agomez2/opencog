/** algo/simple.cc ---
 *
 * Copyright (C) 2011 OpenCog Foundation
 * Copyright (C) 2012 Poulin Holdings LLC
 *
 * Author: Nil Geisweiller
 * Author: Linas Vepstas <linasvepstas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <boost/range/irange.hpp>

#include "simple.h"

namespace opencog {
    
using namespace std;

feature_set simple_select_features(const CTable& ctable,
                                   const feature_selection_parameters& fs_params)
{
    auto ir = boost::irange(0, ctable.get_arity());
    feature_set all_features(ir.begin(), ir.end());
    if (0 == fs_params.target_size)
        // Nothing happened, return all features by default
        return all_features;
        
    typedef MutualInformation<feature_set> FeatureScorer;
    FeatureScorer fsc(ctable);
    return simple_selection(all_features, fsc,
                            fs_params.target_size,
                            fs_params.threshold,
                            fs_params.inc_red_intensity);
}

} // ~namespace opencog

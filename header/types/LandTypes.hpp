#ifndef TES_TYPES_LANDTYPES_HPP
#define TES_TYPES_LANDTYPES_HPP
namespace tes::Types {
using Land_id_t = int;
using land_area = LandArea;
using land_area_ref  = std::reference_wrapper<const land_area>;
}
#endif //TES_TYPES_LANDTYPES_HPP

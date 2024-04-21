#include "vertexcolor_data.h"

#include "servers/rendering_server.h"
#include "servers/rendering/renderer_rd/storage_rd/mesh_storage.h"

void VertexColorData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_colorarray", "p_colorarray"), &VertexColorData::set_colorarray);
	ClassDB::bind_method(D_METHOD("get_colorarray"), &VertexColorData::get_colorarray);

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_COLOR_ARRAY, "color_array"), "set_colorarray", "get_colorarray");
}

void VertexColorData::set_colorarray(PackedColorArray const &p_colorarray) {
	if (rid.is_null()) {
		rid = RS::get_singleton()->vertexcolordata_create();
	}
	RS::get_singleton()->vertexcolordata_set(rid, p_colorarray);
}

PackedColorArray const & VertexColorData::get_colorarray() {
	if (rid.is_null()) {
		colors_cache.clear();
		return colors_cache;
	}
	RS::get_singleton()->vertexcolordata_get(rid,colors_cache);
	return colors_cache;
}

RID VertexColorData::get_rid() const {
	return rid;
}

VertexColorData::VertexColorData() {
}

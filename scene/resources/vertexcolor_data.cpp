#include "vertexcolor_data.h"

#include "servers/rendering_server.h"
#include "servers/rendering/renderer_rd/storage_rd/mesh_storage.h"

void VertexColorData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_colorarray", "p_colorarray"), &VertexColorData::set_colorarray);
	ClassDB::bind_method(D_METHOD("get_colorarray"), &VertexColorData::get_colorarray);
	ClassDB::bind_method(D_METHOD("set_mesh", "mesh_rid"), &VertexColorData::set_mesh);
	ClassDB::bind_method(D_METHOD("get_mesh"), &VertexColorData::get_mesh);

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_COLOR_ARRAY, "color_array"), "set_colorarray", "get_colorarray");
	ADD_PROPERTY(PropertyInfo(Variant::RID, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"), "set_mesh", "get_mesh");
}

void VertexColorData::set_colorarray(PackedColorArray const &p_colorarray) {
	if (rid.is_null()) { return; }
	RS::get_singleton()->vertexcolordata_set(rid, p_colorarray);
	emit_changed();
}

PackedColorArray const &VertexColorData::get_colorarray() {
	if (rid.is_null()) {
		colors_cache.clear();
		return colors_cache;
	}
	RS::get_singleton()->vertexcolordata_get(rid, colors_cache);
	return colors_cache;
}

void VertexColorData::set_mesh(RID mesh_rid) {
	mesh = mesh_rid;
	if (rid.is_null()) {
		rid = RS::get_singleton()->vertexcolordata_create(mesh);
	}
	else {
		// Recreate vertexcolordata with new mesh.
		RS::get_singleton()->free(rid);
		rid = RS::get_singleton()->vertexcolordata_create(mesh);
	}
}

RID VertexColorData::get_mesh() {
	return mesh;
}

RID VertexColorData::get_rid() const {
	return rid;
}

VertexColorData::VertexColorData():
	rid(RID()) {
}

VertexColorData::VertexColorData(RID mesh_rid):
	rid(RID()) {
	set_mesh(mesh_rid);
}

VertexColorData::~VertexColorData() {
	RS::get_singleton()->free(rid);
}

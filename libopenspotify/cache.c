
#include "hashtable.h"
#include "sp_opaque.h"
#include "track.h"
#include "util.h"


void cache_init(sp_session *session) {
	track_load_metadata_from_disk(session, "tracks.cache");
}


int cache_process(sp_session *session, sp_request *req) {
	/* Do some garbage collection */
	track_garbage_collect(session);

	/* Save metadata to disk */
	track_save_metadata_to_disk(session, "tracks.cache");

	req->next_timeout = get_millisecs() + 5*60*1000;

	return 0;
}
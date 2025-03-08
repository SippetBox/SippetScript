#pragma once

enum SippetscriptStatus {
  STATUS_SUCCESS = 0,
  STATUS_UNKNOWN,
};

static inline const char *sippetscript_status_string(
  enum SippetscriptStatus status
) {
  switch (status) {
    case STATUS_SUCCESS: return "STATUS_SUCCESS";
    case STATUS_UNKNOWN: return "STATUS_UNKNOWN";
    default: return "STATUS_UNKNOWN";
  }
}

enum SippetscriptStatus sippetscript(const char *input);
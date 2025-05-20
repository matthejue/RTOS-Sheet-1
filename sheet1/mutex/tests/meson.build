test_files = [
  './queue_test.c',
  './mutex_test.c',
]

test_sources = {
  './queue_test.c': ['../src/queue.c'],
  './mutex_test.c': ['../src/mutex.c'],
}

foreach test_file : test_files
  test_name = test_file.split('/')[-1].split('.')[0]
  test_exe = executable(test_name, [test_file] + test_sources.get(test_file, []),
    include_directories : inc,
    link_with: libmutex)
  test(test_name, test_exe)
endforeach

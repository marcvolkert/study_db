project('study_db', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

unity_dep = dependency('unity')

# ========== UNIT TESTS ==========
# Record
record_test = files([
  'test/record_manager/test_record.c',
  'src/record_manager/offset_record.c']
)

test = executable('test_record', record_test,
  c_args: ['-DUNITY_INCLUDE_CONFIG_H'],
  dependencies : [unity_dep]
)

test('test_record', test)

# ========== EXECUTABLE ==========
executable('study_db', 'study_db.c')

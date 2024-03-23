project('study_db', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

unity_dep = dependency('unity')

# ========== UNIT TESTS ==========
# ------------ record ------------
offset_record_test = files([
  'test/record_manager/test_record.c',
  'src/record_manager/impl/offset_record.c']
)

separator_record_test = files([
  'test/record_manager/test_record.c',
  'src/record_manager/impl/separator_record.c']
)

test_suite_1 = executable('test_suite_1', offset_record_test,
  c_args: ['-DUNITY_INCLUDE_CONFIG_H'],
  dependencies : [unity_dep]
)

test_suite_2 = executable('test_suite_2', separator_record_test,
  c_args: ['-DUNITY_INCLUDE_CONFIG_H'],
  dependencies : [unity_dep]
)

test('test_suite_1', test_suite_1)
test('test_suite_2', test_suite_2)

# ========== EXECUTABLE ==========
executable('study_db', 'study_db.c')

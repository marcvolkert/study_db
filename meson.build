project('study_db', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

unity_dep = dependency('unity')

# ========== UNIT TESTS ==========
# ----------- endecoder ----------
# 1. ASCII endecoder
files_simple_endecoder_test = files([
  'test/endecoder/test_endecoder.c',
  'src/endecoder/impl/simple_endecoder.c']
)

ascii_endecoder_test = executable('simple_endecoder_test', files_simple_endecoder_test,
  c_args: ['-DUNITY_INCLUDE_CONFIG_H'],
  dependencies : [unity_dep]
)

test('simple_endecoder', ascii_endecoder_test)

# ------------ record ------------
# 1. Offset record
endecoder = 'src/endecoder/impl/simple_endecoder.c'

files_offset_record_test = files([
  'test/record_manager/test_record.c',
  'src/record_manager/impl/offset_record.c',
  endecoder]
)

offset_record_test = executable('offset_record_test', files_offset_record_test,
  c_args: ['-DUNITY_INCLUDE_CONFIG_H'],
  dependencies : [unity_dep]
)

test('offset_record_test', offset_record_test)

# 2. Separator record
files_separator_record_test = files([
  'test/record_manager/test_record.c',
  'src/record_manager/impl/separator_record.c',
  endecoder]
)

separator_record_test = executable('separator_record_test', files_separator_record_test,
  c_args: ['-DUNITY_INCLUDE_CONFIG_H'],
  dependencies : [unity_dep]
)

test('separator_record_test', separator_record_test)

# ========== EXECUTABLE ==========
executable('study_db', 'study_db.c')

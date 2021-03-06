dir -r | % {if (
$_ -like "*.cpp" -or
$_ -like "*.c" -or
$_ -like "*.inl" -or
$_ -like "*.cu" -or
$_ -like "*.cc" -or
$_ -like "*.cxx" -or
$_ -like "*.h" -or
$_ -like "*.hxx" -or
$_ -like "*.hpp")
{
.\AStyle.exe --style=allman --indent=tab=8 --align-pointer=type --align-reference=type --indent-preprocessor --break-blocks --pad-oper --pad-paren-in --pad-header --delete-empty-lines --add-brackets --keep-one-line-blocks --keep-one-line-statements --mode=c $_.fullname
}
}
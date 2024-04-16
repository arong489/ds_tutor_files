$tot = Get-Random -Minimum 1 -Maximum 0xfff
$pool = Get-Random -Minimum -2147483648 -Maximum 2147483647 -Count 3

$tot
[int[]]$ans = @()
for ($i = 0; $i -lt $tot; $i++) {
    $ans += Get-Random -InputObject $pool
}
"$ans"
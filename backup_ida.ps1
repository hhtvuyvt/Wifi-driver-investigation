# backup_ida.ps1 — ejecutar después de cada sesión
$src = "C:\Users\hp\Desktop\Camilo\proyectos\C\Wifi-driver-investigation\*.i64"
$dst = "C:\Users\hp\Desktop\Camilo\proyectos\C\Wifi-driver-investigation\backups\"
$date = Get-Date -Format "yyyy-MM-dd_HHmm"
New-Item -ItemType Directory -Force -Path $dst | Out-Null
Copy-Item $src "$dst$i64_$date" -Force
Write-Host "Backup saved: $dst"

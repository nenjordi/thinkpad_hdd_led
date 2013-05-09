# Maintainer: Somebody <nenjordi[at]gmail[dot]com>
pkgname=thinkpad_hdd_led
pkgver=0.0.1
pkgrel=1
pkgdesc="Use thinkpad's power led as hdd led light"
url="https://github.com/nenjordi/thinkpad_hdd_led"
arch=('x86_64' 'i686')
license=('GPLv3')
depends=('gcc')
optdepends=()
makedepends=()
conflicts=()
replaces=()
backup=()
install=''
source=('git://github.com/nenjordi/thinkpad_hdd_led.git')
md5sums=('SKIP')

build() {
  cd "${srcdir}/"
  make
}

package() {
mkdir -p $pkgdir/usr/sbin
make PREFIX="$pkgdir/usr" install
}

# vim:set ts=2 sw=2 et:

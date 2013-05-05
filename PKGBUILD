# Maintainer: Somebody <nenjordi[at]gmail[dot]com>
pkgname=thinkpad_hdd_led
pkgver=0.0.1
pkgrel=1
pkgdesc="Use thinkpad's power led as hdd led light"
url="https://github.com/nenjordi/thinkpad_hdd_led"
arch=('x86_64' 'i686')
license=('GPLv3')
depends=('gcc ')
optdepends=()
makedepends=()
conflicts=()
replaces=()
backup=()
install='thinkpad_hdd_led.install'
source=("http://www.server.tld/${pkgname}-${pkgver}.tar.gz"
        "foo.desktop")
md5sums=('a0afa52d60cea6c0363a2a8cb39a4095'
         'a0afa52d60cea6c0363a2a8cb39a4095')

build() {
  cd "${srcdir}/${pkgname}-${pkgver}"
  make
}

package() {
  cd "${srcdir}/${pkgname}-${pkgver}"
  make DESTDIR="${pkgdir}" install
}

# vim:set ts=2 sw=2 et:
